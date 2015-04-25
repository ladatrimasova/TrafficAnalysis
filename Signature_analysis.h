#ifndef SIGNATURE_ANALISATOR_H
#define SIGNATURE_ANALISATOR_H

#include <fstream>
#include <map>
#include <regex>
#include <vector>
#include <pcap.h>
#include <netinet/in.h>
#include "Pack_headers_struct.h"
#include "Packet.h"
#include "Session.h"
#include "Config.h"



struct Traffic {
    std::string type;
    std::regex signature;
    int priority;

    Traffic(std::string sign, std::string t, int p) : signature(sign), type(t), priority(p) {
    }
};


class Session_data {
private:
    bool solution;
    int solution_priority;
    int solution_num_pack;
    std::string session_solution;
    std::vector<Packet> upload; // *Packet
    std::vector<Packet> download;

public:

    Session_data();

    bool has_solution() const { return solution; }

    std::string get_session_solution() const { return session_solution; }

    void set_session_solution(const std::string& solution, int priority);

    void to_upload(const Packet& pack);

    void to_download(const Packet& pack);

    void print_payload(int length, const u_char *payload) const;

    void clean_session_data();

};


class Signature_analysis {

    std::map<Session, Session_data> sessions_list;

    std::vector<Traffic> sign_type_list;

public:

    Signature_analysis(Config& config);

    void checking_for_signatures(const Packet& pack, Session_data& ) const;

    std::map<Session, Session_data>& get_map() { return sessions_list; } //&?

    void print_sessions_list();

    void add_packet(const Packet& pack);

};

#endif
