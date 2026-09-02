#include "pch.h"
#include "Globals.h"
#include "WebRadar.h"

#pragma comment(lib, "mosquitto.lib")

using namespace std::chrono;
using namespace std::chrono_literals;

WebRadar::WebRadar(Config cfg) : m_cfg(std::move(cfg)) {
    mosquitto_lib_init();
    m_mosq = mosquitto_new(nullptr, true, nullptr);
    if (!m_mosq)
        LOG("WebRadar: mosquitto_new failed\n");
}

WebRadar::~WebRadar() {
    Stop();
    if (m_mosq) {
        mosquitto_destroy(m_mosq);
        m_mosq = nullptr;
    }
    mosquitto_lib_cleanup();
}

void WebRadar::Start() {
    if (m_running.load() || !m_mosq)
        return;

    int rc = mosquitto_connect(m_mosq, m_cfg.brokerHost.c_str(),
                               m_cfg.brokerPort, m_cfg.keepalive);
    if (rc != MOSQ_ERR_SUCCESS) {
        LOG("WebRadar: connect to %s:%d failed (%d)\n",
            m_cfg.brokerHost.c_str(), m_cfg.brokerPort, rc);
        return;
    }

    m_running.store(true);
    m_thread = std::thread(&WebRadar::ThreadProc, this);
    LOG("WebRadar: publishing to %s:%d topic=%s\n",
        m_cfg.brokerHost.c_str(), m_cfg.brokerPort, m_cfg.topic.c_str());
}

void WebRadar::Stop() {
    if (!m_running.exchange(false))
        return;
    if (m_thread.joinable())
        m_thread.join();
    if (m_mosq)
        mosquitto_disconnect(m_mosq);
    LOG("WebRadar: stopped\n");
}

void WebRadar::ThreadProc() {
    while (m_running.load()) {
        auto t0 = steady_clock::now();

        std::string payload = BuildPayload();
        if (!payload.empty()) {
            int rc = mosquitto_publish(m_mosq, nullptr,
                                       m_cfg.topic.c_str(),
                                       static_cast<int>(payload.size()),
                                       payload.data(), 0, false);
            if (rc != MOSQ_ERR_SUCCESS) {
                LOG("WebRadar: publish error %d, reconnecting\n", rc);
                mosquitto_reconnect(m_mosq);
            }
        }

        // Process MQTT network I/O (keepalive pings, ACKs) without blocking.
        mosquitto_loop(m_mosq, 0, 1);

        auto elapsed = duration_cast<milliseconds>(steady_clock::now() - t0);
        auto rem = 50ms - elapsed;
        if (rem > 0ms)
            std::this_thread::sleep_for(rem);
    }
}

std::string WebRadar::BuildPayload() const {
    if (!EngineInstance)
        return {};

    auto actors   = EngineInstance->GetActors();
    auto camCache = EngineInstance->GetCameraCache();
    Vector3 campos(camCache.POV.Location.X,
                   camCache.POV.Location.Y,
                   camCache.POV.Location.Z);

    json doc;
    doc["cam"] = { {"x", campos.x}, {"y", campos.y}, {"z", campos.z} };

    json players = json::array();
    for (const auto& e : actors) {
        if (!e->Class || !e->RootComponent || !e->PlayerState)
            continue;
        if (!e->isCheck || e->Mesh < 65535)
            continue;

        Vector3 head(e->Head3D.X, e->Head3D.Y, e->Head3D.Z);
        if (head.IsZero())
            continue;

        float dist = Vector3::Distance(campos, head) / 100.0f;
        if (dist < 0.0f)
            continue;

        players.push_back({
            {"x",      e->Head3D.X},
            {"y",      e->Head3D.Y},
            {"z",      e->Head3D.Z},
            {"teamId", e->TempId},
            {"isDead", e->isDie},
            {"dist",   dist},
            {"name",   WStringToUTF8(e->Name)}
        });
    }

    doc["players"] = std::move(players);
    return doc.dump();
}

std::string WebRadar::WStringToUTF8(const std::wstring& ws) {
    if (ws.empty())
        return {};
    int sz = WideCharToMultiByte(CP_UTF8, 0,
                                  ws.data(), static_cast<int>(ws.size()),
                                  nullptr, 0, nullptr, nullptr);
    if (sz <= 0)
        return {};
    std::string out(sz, '\0');
    WideCharToMultiByte(CP_UTF8, 0,
                        ws.data(), static_cast<int>(ws.size()),
                        out.data(), sz, nullptr, nullptr);
    return out;
}
