#include "../lib/scanner.h"
#include "../lib/disco.h"
#include "../lib/mount.h"
#include "../lib/filesystem.h"
#include "../lib/report.h"
#include "../lib/users.h"
#include "../lib/filemanager.h"
#include <iostream>
#include <stdlib.h>
#include <locale>
#include <cstring>
#include <locale>
#include <fstream>
#include <vector>
#include <cstdlib>
using namespace std;

Disk disco;
Mount mount;
Report report;
Users user;
Shared shared;
FileManager filemanager;
bool logued = false;
scanner::scanner()
{
}
void Clear()
{
    cout << "\x1B[2J\x1B[H";
}

void scanner::start()
{
    system("clear");
    cout << "\033[48;5;13;38;5;15m" << "╔═════════════════════════════════════════════════════════════════════════════╗" << "\033[0m" << endl;
    cout << "\033[48;5;13;38;5;15m" << "║                            INGRESE UN COMANDO                               ║" << "\033[0m" << endl;
    cout << "\033[48;5;13;38;5;15m" << "╠═════════════════════════════════════════════════════════════════════════════╣" << "\033[0m" << endl;
    cout << "\033[48;5;13;38;5;15m" << "║                             'exit' para salir                               ║" << "\033[0m" << endl;
    cout << "\033[48;5;13;38;5;15m" << "╚═════════════════════════════════════════════════════════════════════════════╝" << "\033[0m" << endl;
    cout << "\033[38;5;13m" << ">> " << "\033[0m" ;
    while (true)
    {
        string texto;
        getline(cin, texto);
        Clear();
        if (compare(texto, "exit"))
        {
            break;
        }
        string tk = token(texto); // mkdisk
        texto.erase(0,tk.length()+1);
        vector<string> tks = split_tokens(texto); //[-size=10, -u=m, -path=/home/hola.dk]
        functions(tk, tks);
        cout << "\nPresione Enter para continuar...." << endl;
        getline(cin,texto);
        Clear();
        cout << "\033[48;5;13;38;5;15m" << "╔═════════════════════════════════════════════════════════════════════════════╗" << "\033[0m" << endl;
        cout << "\033[48;5;13;38;5;15m" << "║                            INGRESE UN COMANDO                               ║" << "\033[0m" << endl;
        cout << "\033[48;5;13;38;5;15m" << "╠═════════════════════════════════════════════════════════════════════════════╣" << "\033[0m" << endl;
        cout << "\033[48;5;13;38;5;15m" << "║                             'exit' para salir                               ║" << "\033[0m" << endl;
        cout << "\033[48;5;13;38;5;15m" << "╚═════════════════════════════════════════════════════════════════════════════╝" << "\033[0m" << endl;
        cout << "\033[38;5;13m" << ">> " << "\033[0m" ;
    }
}
    
void scanner::functions(string token, vector<string> tks)
{
    if (compare(token, "MKDISK")) // mkdisk -s=10 -u=m -path=/home/rauudy/Documentos/Archivos/Pruebas/p1.dsk
                                  // mkdisk -s=10 -path=/home/rauu/Documentos/ProyectoMIA/Pruebas/hola.dsk
                                  // mkdisk -path=/home/rauudy/Documentos/Archivos/Pruebas/hola.dsk -s=10 
    {
        cout << "\033[48;5;226;38;5;0m" << "        FUNCION MKDISK      " << "\033[0m" << endl;
        disco.mkdisk(tks); // [-size=10, -u=m, -path=/home/hola.dk]
    }else if(compare(token, "RMDISK")){
        cout << "\033[48;5;226;38;5;0m" << "        FUNCION RMDISK      " << "\033[0m" << endl;
        disco.rmdisk(tks);
    // rmdisk -path=/home/rauu/Documentos/ProyectoMIA/Pruebas/hola.dsk
    // rmdisk -path=/home/rauudy/Documentos/Archivos/Pruebas/hola.dsk
    }else if(compare(token, "FDISK")){
        cout << "\033[48;5;226;38;5;0m" << "        FUNCION FDISK       " << "\033[0m" << endl;
        disco.fdisk(tks);
    }else if(compare(token, "MOUNT")){
        cout << "\033[48;5;226;38;5;0m" << "        FUNCION MOUNT       " << "\033[0m" << endl;
    // mkdisk -s=3000 -u=m -path=/home/rauudy/Pruebas/Disco10.dsk
    // fdisk -s=300 -path=/home/rauudy/Pruebas/Disco10.dsk -name=Part1
    // mount -path=/home/rauudy/Pruebas/Disco10.dsk -name=Part1 #id=001Disco1 > 651a , 651b
    // con un +1 da 652a, 652b, 652c
    // FUNCIONA
        mount.mount(tks);
        mount.listmount();
    }else if(compare(token, "UNMOUNT")){
        cout << "\033[48;5;226;38;5;0m" << "        FUNCION UNMOUNT     " << "\033[0m" << endl;
        //mount.unmount(tks);
        // unmount -id=631a
        // Funciona cambiar los numeros
        mount.unmount(tks);
    }else if(compare(token, "MKFS")){
        cout << "\033[48;5;226;38;5;0m" << "        FUNCION MKFS        " << "\033[0m" << endl;
        FileSystem fileSystem = FileSystem(mount);
        fileSystem.mkfs(tks);
    }else if(compare(token, "LOGIN")){
        cout << "\033[48;5;226;38;5;0m" << "        FUNCION LOGIN       " << "\033[0m" << endl;
        if(logued){
            shared.handler("LOGIN", " ya existe una sesion abierta");
            return;
        }
        logued = user.login(tks,mount);

    }else if(compare(token, "LOGOUT")){
        cout << "\033[48;5;226;38;5;0m" << "        FUNCION LOGOUT      "<< "\033[0m" << endl;
        if(!logued){
            shared.handler("LOGOUT", " debe de iniciar sesion primero");
            return;
        }
        logued = user.logout();

    }else if(compare(token, "MKGRP")){
        if(!logued){
            shared.handler("MKGRP", " debe de iniciar sesion primero");
            return;
        }
        cout << "\033[48;5;226;38;5;0m" << "        FUNCION MKGRP       " << "\033[0m" << endl;
        user.grp(tks,"MK");

    }else if(compare(token, "RMGRP")){
        if(!logued){
            shared.handler("RMGRP", " debe de iniciar sesion primero");
            return;
        }
        cout << "\033[48;5;226;38;5;0m" << "        FUNCION RMGRP       " << "\033[0m" << endl;
        user.grp(tks,"RM");

    }else if(compare(token, "MKUSR")){
        if(!logued){
            shared.handler("MKUSR", " debe de iniciar sesion primero");
            return;
        }
        cout << "\033[48;5;226;38;5;0m" << "        FUNCION MKUSR       " << "\033[0m" << endl;
        user.usr(tks,"MK");

    }else if(compare(token, "RMUSR")){
        if(!logued){
            shared.handler("RMUSR", " debe de iniciar sesion primero");
            return;
        }
        cout << "\033[48;5;226;38;5;0m" << "        FUNCION RMUSR       " << "\033[0m" << endl;
        user.usr(tks,"RM");

    }else if(compare(token, "MKDIR")){
        if(!logued){
            shared.handler("MKDIR", " debe de iniciar sesion primero");
            return;
        }
        string p;
        cout << "\033[48;5;226;38;5;0m" << "        FUNCION MKDIR       " << "\033[0m" << endl;
        FileSystem fileSystem = FileSystem(mount);
        Structs::Partition partition = mount.getmount(user.logged.id, &p);
        filemanager.mkdir(tks, partition, p);
    }else if(compare(token, "REP")){
        cout << "\033[48;5;226;38;5;0m" << "        FUNCION REPORTES        " << "\033[0m" << endl;
        report.generar(tks, mount);
    }else if(compare(token, "EXEC")){
        cout << "\033[48;5;39;38;5;0m" << "        FUNCION EXEC        " << "\033[0m" << endl;
        funcion_excec(tks);
    }else if(compare(token.substr(0,1),"#")){
        respuesta("COMENTARIO",token);
    }else if(compare(token, "PAUSE")){
        string pause;
        respuesta("PAUSE","Presione enter para continuar...");
        getline(cin,pause);
    }else if(compare(token, "CLS")){
        Clear();
    }else{
        errores("SYSTEM","El comando ingresado no se reconoce en el sistema \""+token+"\"");
    }
}

string scanner::token(string text)
{
    string tkn = "";
    bool terminar = false;
    for (char &c : text){
        if (terminar)
        {
            if (c == ' ' || c == '-'){
                break;
            }
            tkn += c;
        }
        else if ((c != ' ' && !terminar))
        {
            if (c=='#'){
                tkn=text;
                break;
            }else{
                tkn += c;
                terminar = true;
            }
        }
    }
    return tkn;
}

vector<string> scanner::split(string text, string text_split)
{
    vector<string> cadena;
    if (text.empty())
    {
        return cadena;
    }
    
    int n = text.length();
    char char_array[n + 1];
    strcpy(char_array, text.c_str());
    char* point = strtok(char_array, text_split.c_str());
    while (point!=NULL)
    {
        cadena.push_back(string(point));
        point = strtok(NULL, text_split.c_str());
    }
    return cadena;
}

vector<string> scanner::split_tokens(string text){
    vector<string> tokens;
    if (text.empty())
    {
        return tokens;
    }
    text.push_back(' ');
    string token = "";
    int estado = 0;
    for(char &c: text){
        if (estado ==0 && c=='-')
        {
            estado = 1;

        }else if(estado==0 && c=='#'){
            continue;
        }else if(estado!=0){
            if (estado == 1)
            {
                if(c=='='){
                    estado = 2;
                }else if(c == ' '){
                    continue;
                }
            }else if(estado == 2){
                if (c=='\"')
                {
                    estado = 3;
                }else{
                    estado = 4;
                }
                
            }else if(estado == 3){
                if (c=='\"')
                {
                    estado = 4;
                }
            }else if (estado==4 && c=='\"')
            {
                tokens.clear();
                continue;
            }else if (estado ==4 && c==' ')
            {
                estado = 0;
                tokens.push_back(token);
                token = "";
                continue;
            }
            token+=c;
        }
    }
    return tokens;
}

string scanner::upper(string a){
    string up="";
    for(char &a: a){
        up+=toupper(a);
    }
    return up;  
}

bool scanner::compare(string a, string b){
    if (upper(a)==upper(b))
    {
        return true;
    }
    return false;
}

void scanner::errores(string operacion, string mensaje){
    
    cout << "\033[1;41m Error\033"<< "\033[0;31m(" + operacion + ")~~> \033[0m"<< mensaje << endl;
}

void scanner::respuesta(string operacion, string mensaje){
    if (compare(operacion, "COMENTARIO"))
    {
        cout << "\033[1;35;44m(" + operacion + ")~~> \033[0m"<< mensaje << endl;
        return;
    }else if(compare(operacion, "PAUSE")){
        cout << "\033[1;16;47m(" + operacion + ")~~> \033[0m"<< mensaje << endl;
    }
    else{
        cout << "\033[1;32;47m(" + operacion + ")~~> \033[0m"<< mensaje << endl;
    }
}

bool scanner::confirmar(string mensaje){
    cout << mensaje << "Confirmar(S), cualquier otra letra para cancelar: ";
    string respuesta;
    getline(cin,respuesta);
    if (compare(respuesta, "s"))
    {
        return true;
    }
    return false;
    
}

void scanner::funcion_excec(vector<string> tokens){
    string path = "";
    for (string token:tokens)
    {
        string tk = token.substr(0, token.find("="));
        token.erase(0,tk.length()+1);
        if (compare(tk, "path"))
        {
            path = token;
        }
    }
    if (path.empty())
    {
        errores("EXEC","Se requiere path para este comando");
        return;
    }
    excec(path);
}

void scanner::excec(string path){
    string filename(path);
    vector <string> lines;
    string line;
    ifstream input_file(filename);
    if(!input_file.is_open()){
        cerr << "No se puede abrir el archivo" << filename << endl;
        return;
    }
    while(getline(input_file,line)){
        lines.push_back(line);
    }
    for(const auto &i:lines){
        string texto = i;
        string tk = token(texto);
        if(texto!=""){
            if(compare(texto,"PAUSE")){
                string pause;
                respuesta("PAUSE","Presione enter para continuar...");
                getline(cin,pause);
                continue;
            }
            texto.erase(0,tk.length()+1);
            vector <string> tks = split_tokens(texto);
            functions(tk,tks);
        }
    }
    input_file.close();
    return;
}