#ifndef CLICK_FlowIPManagerHMPMP_HH
#define CLICK_FlowIPManagerHMPMP_HH
#include <click/config.h>
#include <click/string.hh>
#include <click/timer.hh>
#include <click/vector.hh>
#include <click/multithread.hh>
#include <click/batchelement.hh>
#include <click/hashtablemp.hh>
#include <click/pair.hh>
#include <click/ipflowid.hh>
#include <click/flow/common.hh>


#include "../flow/flowipmanagermp.hh"



CLICK_DECLS


class FlowIPManagerHMP: public FlowIPManagerMP {
public:


    FlowIPManagerHMP() CLICK_COLD;

	~FlowIPManagerHMP() CLICK_COLD;

    const char *class_name() const		{ return "FlowIPManagerHMP"; }
    const char *port_count() const		{ return "1/1"; }


    //int configure(Vector<String> &, ErrorHandler *) CLICK_COLD;
    int initialize(ErrorHandler *errh) override CLICK_COLD;
    void cleanup(CleanupStage stage) override CLICK_COLD;

    //First : group id, second : destination cpu
    void pre_migrate(DPDKDevice* dev, int from, Vector<Pair<int,int>> gids);
    void post_migrate(DPDKDevice* dev, int from);


    void push_batch(int, PacketBatch* batch) override;

    void init_assignment(Vector<unsigned> table);

private:


    HashTableMP<IPFlow5ID,int> _hash;
    atomic_uint32_t _current;

    inline void process(Packet* p, BatchBuilder& b);

};



CLICK_ENDDECLS
#endif
