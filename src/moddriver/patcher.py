import sys

VERSION = "0.0.2"

def getPatchName(filepath):
    structure = open(filepath, "rb").read()[5:]
    name = ""
    for char in list(structure):
        if char == 0:
            break
        else:
            name += chr(char)
    return name

def patch(filepath, spwnexepath):
    print("MDDR IPS patcher v"+VERSION)
    with open(filepath, "rb") as f:
        data = f.read()
    if not data.startswith(b"PATCH"):
        raise ValueError("Invalid patch file (missing header)")
    
    offset = data.index(0x00, 5) + 1

    packets = []
    while offset < len(data):
        if offset + 4 > len(data):
            break

        addr = data[offset:offset+3]
        length = data[offset+3]
        content = data[offset+4:offset+4+length]

        packets.append((addr, content))
        offset += 4 + length

    print(str(len(packets))+" packets to do.")
    print(f"Writing to {spwnexepath}")

    with open(spwnexepath, "rb") as f:
        exedata = bytearray(f.read())

    for i, (addr, content) in enumerate(packets, start=1):
        offset = int.from_bytes(addr, "big")
        end = offset + len(content)
        if end > len(exedata):
            exedata.extend(b"\x00" * (end - len(exedata)))
        exedata[offset:end] = content
        sys.stdout.write(f"\r[{i}/{len(packets)}] Patching...")
        sys.stdout.flush()

    sys.stdout.write("\r")
    print(f"Finished patching {len(packets)} packets. Thank you.")
    
    outpath = spwnexepath
    with open(outpath, "wb") as f:
        f.write(exedata)