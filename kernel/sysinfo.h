struct sysinfo{
    uint64 freemem; // number of bytes of free memory
    uint64 nproc; // number of processes whose state is not UNUSED
    uint64 nopenfiles; // number of opening files in whole system
};