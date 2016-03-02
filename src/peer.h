#ifndef PEER_H
#define PEER_H

#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "spiffy.h"
#include "chunk.h"
#include "bt_parse.h"
#include "input_buffer.h"
#include "uthash.h"

#include "packet.h"

/* Macros */

#define HASH_SIZE     20
#define PORT_LEN      10
#define PEER_KEY_LEN  INET_ADDRSTRLEN + 5 + PORT_LEN

typedef struct chunk_table chunk_table;
typedef struct peer peer;

/* Structs */

struct chunk_table {

  uint8_t        chunk[HASH_SIZE];  // Key
  size_t         id;
  UT_hash_handle hh;

};

struct peer {

  int                id;
  int                timeoutfd;

  /* Format:         "address:port" */
  char               key[PEER_KEY_LEN];
  struct sockaddr_in addr;

  chunk_table*       has_chunks;
  struct byte_buf*   buf;

  UT_hash_handle     hh;

};


/* Prototypes */

void peer_run(bt_config_t *config);
void process_inbound_udp(int sock);
void process_get(char *chunkfile, char *outputfile);
void handle_user_input(char *line, void *cbdata);

void global_populate(bt_config_t* config);
void convert_LL2HT(bt_peer_t* ll_peers, peer** ht_peers);
void make_chunktable(char* chunk_file, chunk_table** table, int flag);

#endif