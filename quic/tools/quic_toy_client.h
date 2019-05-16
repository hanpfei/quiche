// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// A toy client, which connects to a specified port and sends QUIC
// requests to that endpoint.

#ifndef QUICHE_QUIC_TOOLS_QUIC_TOY_CLIENT_H_
#define QUICHE_QUIC_TOOLS_QUIC_TOY_CLIENT_H_

#include "net/third_party/quiche/src/quic/tools/quic_client.h"

namespace quic {

class QuicToyClientBase {
 public:
  class ClientFactory {
   public:
    virtual ~ClientFactory() = default;

    // Creates a new client configured to connect to |host:port| supporting
    // |versions|, and using |verifier| to verify proofs.
    virtual std::unique_ptr<QuicSpdyClientBase> CreateClient(
        std::string host,
        uint16_t port,
        ParsedQuicVersionVector versions,
        std::unique_ptr<ProofVerifier> verifier) = 0;
  };

  // Constructs a new toy client that will use |client_factory| to create the
  // actual QuicSpdyClientBase instance.
  QuicToyClientBase(ClientFactory* client_factory);

  // Connects to the QUIC server based on the various flags defined in the
  // .cc file, sends requests and prints the responses. Returns 0 on success
  // and non-zero otherwise.
  int SendRequestsAndPrintResponses(std::vector<std::string> urls);

 private:
  ClientFactory* client_factory_;  // Unowned.
};

}  // namespace quic

#endif  // QUICHE_QUIC_TOOLS_QUIC_TOY_CLIENT_H_
