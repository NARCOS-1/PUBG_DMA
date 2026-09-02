#pragma once
#include <Mosquitto/mosquitto.h>
#include <atomic>
#include <thread>
#include <string>

// Publishes player radar data as JSON over MQTT every 50 ms.
// Place mosquitto.h in $(SolutionDir)Include and mosquitto.lib in $(SolutionDir)Lib.
// Copy mosquitto.dll next to the built executable before running.
class WebRadar {
public:
    struct Config {
        std::string brokerHost = "127.0.0.1";
        int         brokerPort = 1883;
        std::string topic      = "pubg/radar";
        int         keepalive  = 60;
    };

    explicit WebRadar(Config cfg = {});
    ~WebRadar();

    WebRadar(const WebRadar&)            = delete;
    WebRadar& operator=(const WebRadar&) = delete;

    void Start();
    void Stop();

private:
    void        ThreadProc();
    std::string BuildPayload() const;
    static std::string WStringToUTF8(const std::wstring& ws);

    Config            m_cfg;
    std::atomic<bool> m_running{ false };
    std::thread       m_thread;
    mosquitto*        m_mosq = nullptr;
};
