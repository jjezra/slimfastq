//
// Written by Josef Ezra <jezra@infinidat.com> during R&D phase.
// Please do not use without author's explicit permission.
// 

#ifndef FQ_GENS_H
#define FQ_GENS_H

#include "common.hpp"
#include "config.hpp"
#include "pager.hpp"
#include <stdio.h>

#include "filer.hpp"
#include "bases_ranger.hpp"

class GenBase {
protected:

    struct {
        UINT64 count;
        UINT64 Ns_index;
        UINT64 Nn_index;
    } m_last;
        
    const Config* m_conf;

    struct {
        UINT32 big_gaps;
    } m_stats ;

    bool   m_lossless, m_valid;
    UCHAR  m_N_byte;

};

class GenSave : private GenBase {
public:
    GenSave(const Config* conf);
    ~GenSave();

    void save(const UCHAR* gen, UCHAR* qlt, size_t size);
    void pager_init();

private:
    void putgapNs(UINT64 gap);
    void putgapNn(UINT64 gap);

    PagerSave02* pager;
    PagerSave16* pagerNs;
    PagerSave16* pagerNn;

};

class GenLoad : private GenBase {
public:
    GenLoad(const Config* conf);
    ~GenLoad();

    UINT32 load(UCHAR* gen, const UCHAR* qlt, size_t size);

private:
    UCHAR get_2();
    UINT64 getgapNs();
    UINT64 getgapNn();

    bool   m_validNs, m_validNn;
    const char* m_gencode;

    PagerLoad02* pager;
    PagerLoad16* pagerNs;
    PagerLoad16* pagerNn;
};


#endif //  FQ_GENS_H
