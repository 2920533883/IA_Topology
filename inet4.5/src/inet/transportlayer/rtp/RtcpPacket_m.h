//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/transportlayer/rtp/RtcpPacket.msg.
//

#ifndef __INET_RTCPPACKET_M_H
#define __INET_RTCPPACKET_M_H

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


}  // namespace inet


namespace inet {
namespace rtp {

class RtcpPacket;
class RtcpReceiverReportPacket;
class RtcpSdesPacket;
class RtcpByePacket;
class RtcpSenderReportPacket;

}  // namespace rtp
}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

#include "inet/transportlayer/rtp/Reports_m.h" // import inet.transportlayer.rtp.Reports

// cplusplus {{
#include "inet/transportlayer/rtp/Sdes.h"
// }}


namespace inet {


}  // namespace inet


namespace inet {
namespace rtp {

/**
 * Enum generated from <tt>inet/transportlayer/rtp/RtcpPacket.msg:18</tt> by opp_msgtool.
 * <pre>
 * enum RtcpPacketType
 * {
 *     RTCP_PT_UNDEF = 0; // default value undefined
 *     RTCP_PT_SR = 200; // sender report
 *     RTCP_PT_RR = 201; // receiver report
 *     RTCP_PT_SDES = 202; // source description
 *     RTCP_PT_BYE = 203; // bye
 * }
 * </pre>
 */
enum RtcpPacketType {
    RTCP_PT_UNDEF = 0,
    RTCP_PT_SR = 200,
    RTCP_PT_RR = 201,
    RTCP_PT_SDES = 202,
    RTCP_PT_BYE = 203
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RtcpPacketType& e) { b->pack(static_cast<int>(e)); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RtcpPacketType& e) { int n; b->unpack(n); e = static_cast<RtcpPacketType>(n); }

/**
 * Class generated from <tt>inet/transportlayer/rtp/RtcpPacket.msg:27</tt> by opp_msgtool.
 * <pre>
 * class RtcpPacket extends FieldsChunk
 * {
 *     chunkLength = B(4);
 *     int8_t version = 2;
 *     bool padding = 0;   // (1 bits) Used to indicate if there are extra padding bytes at the end of the RTP packet. A padding might be used to fill up a block of certain size, for example as required by an encryption algorithm. The last byte of the padding contains the number of padding bytes that were added (including itself).
 *     short count = 0;    // RC (Reception report count ): (5 bits) The number of reception report blocks contained in this packet. A value of zero is valid.
 *     RtcpPacketType packetType = RTCP_PT_UNDEF;      // (8 bits) Contains a constant to identify RTCP packet type.
 *     int rtcpLength = 0;     // (16 bits) Indicates The length of this RTCP packet in 32-bit words minus one, including the header and any padding.
 * }
 * </pre>
 */
class INET_API RtcpPacket : public ::inet::FieldsChunk
{
  protected:
    int8_t version = 2;
    bool padding = 0;
    short count = 0;
    RtcpPacketType packetType = RTCP_PT_UNDEF;
    int rtcpLength = 0;

  private:
    void copy(const RtcpPacket& other);

  protected:
    bool operator==(const RtcpPacket&) = delete;

  public:
    RtcpPacket();
    RtcpPacket(const RtcpPacket& other);
    virtual ~RtcpPacket();
    RtcpPacket& operator=(const RtcpPacket& other);
    virtual RtcpPacket *dup() const override {return new RtcpPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual int8_t getVersion() const;
    virtual void setVersion(int8_t version);

    virtual bool getPadding() const;
    virtual void setPadding(bool padding);

    virtual short getCount() const;
    virtual void setCount(short count);

    virtual RtcpPacketType getPacketType() const;
    virtual void setPacketType(RtcpPacketType packetType);

    virtual int getRtcpLength() const;
    virtual void setRtcpLength(int rtcpLength);


  public:
    /** padding RtcpPacket to 32 bit words and set the rtcpLength field (based on chunkLength field) **/
    void paddingAndSetLength();
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RtcpPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RtcpPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/rtp/RtcpPacket.msg:43</tt> by opp_msgtool.
 * <pre>
 * class RtcpReceiverReportPacket extends RtcpPacket
 * {
 *     packetType = RTCP_PT_RR;
 *     chunkLength = getChunkLength() + B(4);
 *     uint32_t ssrc = 0;
 *     cArray receptionReports;
 * }
 * </pre>
 */
class INET_API RtcpReceiverReportPacket : public ::inet::rtp::RtcpPacket
{
  protected:
    uint32_t ssrc = 0;
    ::omnetpp::cArray receptionReports;

  private:
    void copy(const RtcpReceiverReportPacket& other);

  protected:
    bool operator==(const RtcpReceiverReportPacket&) = delete;

  public:
    RtcpReceiverReportPacket();
    RtcpReceiverReportPacket(const RtcpReceiverReportPacket& other);
    virtual ~RtcpReceiverReportPacket();
    RtcpReceiverReportPacket& operator=(const RtcpReceiverReportPacket& other);
    virtual RtcpReceiverReportPacket *dup() const override {return new RtcpReceiverReportPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual uint32_t getSsrc() const;
    virtual void setSsrc(uint32_t ssrc);

    virtual const ::omnetpp::cArray& getReceptionReports() const;
    virtual ::omnetpp::cArray& getReceptionReportsForUpdate() { handleChange();return const_cast<::omnetpp::cArray&>(const_cast<RtcpReceiverReportPacket*>(this)->getReceptionReports());}
    virtual void setReceptionReports(const ::omnetpp::cArray& receptionReports);


  public:
    /** Adds a receiver report to this receiver report packet. */
    virtual void addReceptionReport(ReceptionReport *report);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RtcpReceiverReportPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RtcpReceiverReportPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/rtp/RtcpPacket.msg:57</tt> by opp_msgtool.
 * <pre>
 * class RtcpSdesPacket extends RtcpPacket
 * {
 *     packetType = RTCP_PT_SDES;
 *     cArray sdesChunks;
 * }
 * </pre>
 */
class INET_API RtcpSdesPacket : public ::inet::rtp::RtcpPacket
{
  protected:
    ::omnetpp::cArray sdesChunks;

  private:
    void copy(const RtcpSdesPacket& other);

  protected:
    bool operator==(const RtcpSdesPacket&) = delete;

  public:
    RtcpSdesPacket();
    RtcpSdesPacket(const RtcpSdesPacket& other);
    virtual ~RtcpSdesPacket();
    RtcpSdesPacket& operator=(const RtcpSdesPacket& other);
    virtual RtcpSdesPacket *dup() const override {return new RtcpSdesPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const ::omnetpp::cArray& getSdesChunks() const;
    virtual ::omnetpp::cArray& getSdesChunksForUpdate() { handleChange();return const_cast<::omnetpp::cArray&>(const_cast<RtcpSdesPacket*>(this)->getSdesChunks());}
    virtual void setSdesChunks(const ::omnetpp::cArray& sdesChunks);


  public:
    void addSDESChunk(SdesChunk *sdesChunk);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RtcpSdesPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RtcpSdesPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/rtp/RtcpPacket.msg:68</tt> by opp_msgtool.
 * <pre>
 * class RtcpByePacket extends RtcpPacket
 * {
 *     packetType = RTCP_PT_BYE;
 *     chunkLength = getChunkLength() + B(4);
 *     count = 1;
 *     uint32_t ssrc = 0;
 * }
 * </pre>
 */
class INET_API RtcpByePacket : public ::inet::rtp::RtcpPacket
{
  protected:
    uint32_t ssrc = 0;

  private:
    void copy(const RtcpByePacket& other);

  protected:
    bool operator==(const RtcpByePacket&) = delete;

  public:
    RtcpByePacket();
    RtcpByePacket(const RtcpByePacket& other);
    virtual ~RtcpByePacket();
    RtcpByePacket& operator=(const RtcpByePacket& other);
    virtual RtcpByePacket *dup() const override {return new RtcpByePacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual uint32_t getSsrc() const;
    virtual void setSsrc(uint32_t ssrc);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RtcpByePacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RtcpByePacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/rtp/RtcpPacket.msg:76</tt> by opp_msgtool.
 * <pre>
 * class RtcpSenderReportPacket extends RtcpReceiverReportPacket
 * {
 *     packetType = RTCP_PT_SR;
 *     chunkLength = getChunkLength() + B(20);
 *     SenderReport senderReport;
 * }
 * </pre>
 */
class INET_API RtcpSenderReportPacket : public ::inet::rtp::RtcpReceiverReportPacket
{
  protected:
    SenderReport senderReport;

  private:
    void copy(const RtcpSenderReportPacket& other);

  protected:
    bool operator==(const RtcpSenderReportPacket&) = delete;

  public:
    RtcpSenderReportPacket();
    RtcpSenderReportPacket(const RtcpSenderReportPacket& other);
    virtual ~RtcpSenderReportPacket();
    RtcpSenderReportPacket& operator=(const RtcpSenderReportPacket& other);
    virtual RtcpSenderReportPacket *dup() const override {return new RtcpSenderReportPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const SenderReport& getSenderReport() const;
    virtual SenderReport& getSenderReportForUpdate() { handleChange();return const_cast<SenderReport&>(const_cast<RtcpSenderReportPacket*>(this)->getSenderReport());}
    virtual void setSenderReport(const SenderReport& senderReport);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RtcpSenderReportPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RtcpSenderReportPacket& obj) {obj.parsimUnpack(b);}


}  // namespace rtp
}  // namespace inet


namespace omnetpp {

template<> inline inet::rtp::RtcpPacket *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::rtp::RtcpPacket*>(ptr.get<cObject>()); }
template<> inline inet::rtp::RtcpReceiverReportPacket *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::rtp::RtcpReceiverReportPacket*>(ptr.get<cObject>()); }
template<> inline inet::rtp::RtcpSdesPacket *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::rtp::RtcpSdesPacket*>(ptr.get<cObject>()); }
template<> inline inet::rtp::RtcpByePacket *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::rtp::RtcpByePacket*>(ptr.get<cObject>()); }
template<> inline inet::rtp::RtcpSenderReportPacket *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::rtp::RtcpSenderReportPacket*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __INET_RTCPPACKET_M_H

