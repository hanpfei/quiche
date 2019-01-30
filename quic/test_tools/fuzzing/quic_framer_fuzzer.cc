#include "base/commandlineflags.h"
#include "net/third_party/quiche/src/quic/core/crypto/crypto_framer.h"
#include "net/third_party/quiche/src/quic/core/crypto/crypto_handshake_message.h"
#include "net/third_party/quiche/src/quic/core/quic_framer.h"
#include "net/third_party/quiche/src/quic/core/quic_packets.h"
#include "net/third_party/quiche/src/quic/platform/api/quic_string_piece.h"
#include "net/third_party/quiche/src/quic/test_tools/quic_test_utils.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  SetQuicFlag(&FLAGS_minloglevel, 3);

  quic::QuicFramer framer(quic::AllSupportedVersions(), quic::QuicTime::Zero(),
                          quic::Perspective::IS_SERVER);
  const char* const packet_bytes = reinterpret_cast<const char*>(data);

  // Test the CryptoFramer.
  quic::QuicStringPiece crypto_input(packet_bytes, size);
  std::unique_ptr<quic::CryptoHandshakeMessage> handshake_message(
      quic::CryptoFramer::ParseMessage(crypto_input));

  // Test the regular QuicFramer with the same input.
  quic::test::NoOpFramerVisitor visitor;
  framer.set_visitor(&visitor);
  quic::QuicEncryptedPacket packet(packet_bytes, size);
  framer.ProcessPacket(packet);

  return 0;
}