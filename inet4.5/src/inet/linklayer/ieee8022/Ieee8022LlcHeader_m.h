//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/linklayer/ieee8022/Ieee8022LlcHeader.msg.
//

#ifndef __INET_IEEE8022LLCHEADER_M_H
#define __INET_IEEE8022LLCHEADER_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

// dll export symbol
#ifndef INET_API
#  if defined(INET_EXPORT)
#    define INET_API  OPP_DLLEXPORT
#  elif defined(INET_IMPORT)
#    define INET_API  OPP_DLLIMPORT
#  else
#    define INET_API
#  endif
#endif


namespace inet {

class Ieee8022LlcHeader;

}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk


namespace inet {

/**
 * Class generated from <tt>inet/linklayer/ieee8022/Ieee8022LlcHeader.msg:24</tt> by opp_msgtool.
 * <pre>
 * //
 * // This chunk represents an IEEE 802.2 LLC header as defined by the ANSI/IEEE
 * // Std 802.2, 1998, IEEE Standard for Information technology, Telecommunications
 * // and information exchange between systems, Local and metropolitan area networks.
 * //
 * //  0                   1                   2
 * //  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
 * // +---------------+---------------+---------------+
 * // |      DSAP     |      SSAP     |    CONTROL    |
 * // +---------------+---------------+---------------+
 * //
 * class Ieee8022LlcHeader extends FieldsChunk
 * {
 *     chunkLength = B(3);
 *     short dsap = -1;    // 1 byte
 *     short ssap = -1;    // 1 byte
 *     int control = -1;    // 1 or 2 byte, control = byte[0]+256*byte[1], two bytes, when (byte[0] & 3) != 3
 * }
 * </pre>
 */
class INET_API Ieee8022LlcHeader : public ::inet::FieldsChunk
{
  protected:
    short dsap = -1;
    short ssap = -1;
    int control = -1;

  private:
    void copy(const Ieee8022LlcHeader& other);

  protected:
    bool operator==(const Ieee8022LlcHeader&) = delete;

  public:
    Ieee8022LlcHeader();
    Ieee8022LlcHeader(const Ieee8022LlcHeader& other);
    virtual ~Ieee8022LlcHeader();
    Ieee8022LlcHeader& operator=(const Ieee8022LlcHeader& other);
    virtual Ieee8022LlcHeader *dup() const override {return new Ieee8022LlcHeader(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual short getDsap() const;
    virtual void setDsap(short dsap);

    virtual short getSsap() const;
    virtual void setSsap(short ssap);

    virtual int getControl() const;
    virtual void setControl(int control);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee8022LlcHeader& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee8022LlcHeader& obj) {obj.parsimUnpack(b);}


}  // namespace inet


namespace omnetpp {

template<> inline inet::Ieee8022LlcHeader *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::Ieee8022LlcHeader*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __INET_IEEE8022LLCHEADER_M_H

