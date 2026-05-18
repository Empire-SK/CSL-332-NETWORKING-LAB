# CSL-332 Networking Lab

This repository contains C programs for common networking-lab experiments and supporting Linux networking command notes.

## Repository Structure

- `network_commands.txt` - Notes for basic networking commands (`ifconfig`, `netstat`, `ping`, `arp`, `telnet`, `tnftp`)
- `DVR/` - Distance Vector Routing (shortest-path simulation)
- `FTP/` - Simple file transfer using TCP sockets (client/server)
- `Leaky Bucket/` - Leaky bucket traffic-shaping simulations
- `SMTP/` - Basic SMTP-like mail transfer (client/server)
- `Stop And Wait/` - Stop-and-Wait ARQ protocol simulation
- `TCP/` - TCP client/server sum calculator
- `UDP/` - UDP client/server sum calculator

## Requirements

- GCC compiler
- A terminal (Git Bash on Windows works fine)

Check compiler:

```bash
gcc --version
```

## Build Commands

Run these from the repository root:

```bash
# DVR
gcc -o DVR/program.exe DVR/program.c

# FTP
gcc -o FTP/client.exe FTP/client.c
gcc -o FTP/server.exe FTP/server.c

# Leaky Bucket
gcc -o "Leaky Bucket/leaky.exe" "Leaky Bucket/leaky.c"
gcc -o "Leaky Bucket/Leakybucket.exe" "Leaky Bucket/Leakybucket.c"

# SMTP
gcc -o SMTP/client.exe SMTP/client.c
gcc -o SMTP/server.exe SMTP/server.c

# Stop And Wait
gcc -o "Stop And Wait/client.exe" "Stop And Wait/client.c"
gcc -o "Stop And Wait/server.exe" "Stop And Wait/server.c"

# TCP
gcc -o TCP/sumclient.exe TCP/sumclient.c
gcc -o TCP/sumserver.exe TCP/sumserver.c

# UDP
gcc -o UDP/client.exe UDP/client.c
gcc -o UDP/server.exe UDP/server.c
```

## Experiment-Wise Run Guide

## 1) DVR

Purpose: Computes shortest paths using a routing-style cost matrix.

Run:

```bash
./DVR/program.exe
```

Inputs:
- Number of nodes
- Cost matrix values

## 2) FTP (TCP)

Purpose: Transfers a file from server to client.

Run server first:

```bash
./FTP/server.exe
```

Then run client in another terminal:

```bash
./FTP/client.exe
```

Inputs:
- Server and client both ask for port number (use same port)
- File name to fetch
- New file name to save locally

## 3) Leaky Bucket

Purpose: Simulates traffic shaping and packet drop behavior.

Run either version:

```bash
./Leaky\ Bucket/leaky.exe
# or
./Leaky\ Bucket/Leakybucket.exe
```

Inputs include bucket size, output rate, and packet sizes.

## 4) SMTP

Purpose: Sends and receives a basic email-like message.

Run server first:

```bash
./SMTP/server.exe
```

Run client in another terminal:

```bash
./SMTP/client.exe
```

Notes:
- Uses hardcoded port `8082`
- Client asks for sender, recipient, and body
- End message body with `$`

## 5) Stop And Wait ARQ

Purpose: Demonstrates ACK/NAK-based reliable transfer.

Run server first:

```bash
./Stop\ And\ Wait/server.exe
```

Run client in another terminal:

```bash
./Stop\ And\ Wait/client.exe
```

Notes:
- Uses hardcoded port `5651`
- Server asks whether each packet is received (`1` for ACK, `0` for NAK)

## 6) TCP Sum Client/Server

Purpose: Sends two numbers from client, server returns sum.

Run server first:

```bash
./TCP/sumserver.exe
```

Run client in another terminal:

```bash
./TCP/sumclient.exe
```

Notes:
- Uses hardcoded port `3003`

## 7) UDP Sum Client/Server

Purpose: Sends two numbers via UDP, server returns sum.

Run server first:

```bash
./UDP/server.exe
```

Run client in another terminal:

```bash
./UDP/client.exe
```

Notes:
- Uses hardcoded port `12345`

## Quick Tips

- Start server before client for all client/server experiments.
- If a port is already in use, stop the running process or change the port (where supported).
- Most clients connect to localhost (`127.0.0.1`) by default.
- Keep separate terminal windows for server and client programs.

## Author

Networking Lab repository for CSL-332 coursework.
