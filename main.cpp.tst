#include <iostream>
#include <stdexcept>
#include <tins/tins.h>

using namespace std;
using namespace Tins;

// Define your probe request callback function here
void on_probe_request(const Dot11ProbeRequest& request) {
    // Handle probe request (e.g., print SSID, MAC address, etc.)
    cout << "Probe Request: SSID=" << request.ssid() << ", MAC=" << request.addr2() << endl;
}

bool handle_packet(PDU& packet) {
    if (packet.pdu_type() == PDU::DOT11_PROBE_REQ) {
        const Dot11ProbeRequest& request = packet.rfind_pdu<Dot11ProbeRequest>();
        on_probe_request(request);
    }

    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <interface>" << endl;
        return 1;
    }

    try {
        SnifferConfiguration config;
        config.set_immediate_mode(true);
        config.set_filter("wlan type mgt subtype probe-req"); // Adjust the filter

        Sniffer sniffer(argv[1], config);
        cout << "Starting probe request capture on interface " << argv[1] << endl;

        sniffer.sniff_loop(handle_packet);
        
    } catch (exception& ex) {
        cerr << "Error: " << ex.what() << endl;
        return 1;
    }
}