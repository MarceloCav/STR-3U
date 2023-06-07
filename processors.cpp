#include "processors.h"

using namespace std;


void processors::setProcess_nome(std::string newProcess_nome)
{
    *process_nome = newProcess_nome;
}

processors::processors()
{
    process_nome = new string;
    *process_nome = "null";
}

processors::~processors()
{
    system("rm processos.txt");
    delete process_nome;
}

std::vector<std::vector<string> > processors::get_processors()
{
    std::vector<std::vector<std::string>> proc;

    string comando;
    if(*process_nome == "null"){
        comando = "ps fo pid,cpuid,user,pri,ni,state,%cpu,%mem,time,command -A > processos.txt";
    } else {
        comando = "ps fo pid,cpuid,user,pri,ni,state,%cpu,%mem,time,command -C "+ *process_nome + " > processos.txt";
    }
    system(comando.c_str());

    ifstream arquivo;
    vector <string> frase;

    arquivo.open("processos.txt");

    if(!arquivo.is_open()){
        frase.push_back("Erro!");
        proc.push_back(frase);
    }

    char delimitador[] = " ";
    string aux_frase;
    size_t pos;
    int j;
    while(getline(arquivo, aux_frase)){
        j = 0;
        frase.clear();
        while(j < 9){
            while(aux_frase.at(0) == delimitador[0]){
                aux_frase.erase(0,1);
            }
            pos = aux_frase.find(delimitador);
            frase.push_back(aux_frase.substr(0, pos));
            aux_frase.erase(0, pos + 1);
            j++;
        }
        frase.push_back(aux_frase);
        proc.push_back(frase);
    }

    arquivo.close();
    return proc;
}

void processors::kill_process(int pid)
{
    kill(pid, SIGKILL);
}

void processors::stop_process(int pid)
{
    kill(pid, SIGSTOP);
}

void processors::cont_process(int pid)
{
    kill(pid, SIGCONT);
}

void processors::set_CPU(std::string pid, std::string cpu)
{
    string comando = "taskset -pc "+cpu+" "+pid;
    system(comando.c_str());
}

void processors::set_prio(int pid, int prio)
{
    setpriority(PRIO_PROCESS, pid , prio);
}


