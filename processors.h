#ifndef PROCESSORS_H
#define PROCESSORS_H
#include<iostream>
#include<fstream>
#include <stdlib.h> // system()
#include <signal.h> // definição dos sinais de interrupções
#include <unistd.h>
#include <sys/time.h>     // getpriority(int which, int who)  setpriority(int which, int who, int prio);
#include <sys/resource.h>
#include <vector>

class processors
{
private:
    std::string* process_nome;

public:
    processors();
    ~processors();
    std::vector<std::vector<std::string>> get_processors();
    void kill_process(int pid);
    void stop_process(int pid);
    void cont_process(int pid);
    void set_CPU(std::string pid, std::string cpu);
    void set_prio(int pid, int prio);

    void setProcess_nome(std::string newProcess_nome);
};

#endif // PROCESSORS_H
