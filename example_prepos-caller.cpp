/*
prepos_caller: A minimal library for wrapping object methods calls.
    Copyright (C) 2008, 2009  Daniel Gutson, FuDePAN

    This file is part of the MiLi Minimalistic Library.

    MiLi is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    MiLi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MiLi.  If not, see <http://www.gnu.org/licenses/>.

    This is the sample cpp program, that shows how to use PrePosCaller.
*/
#include "include/mili.h"
#include "include/prepos_printer.h"
#include "include/prepos_mutex.h"

using namespace std;

class Test
{
public:
    void f() { cout << "f" << endl; }
};


///

void sample_using_print()
{
    cout << "Sample using print:\n";
    Test t;
    PrePosPrinter pre("pre"), pos("pos");
    PrePosCaller<Test* const, PrePosPrinter, PrePosPrinter> ppc(&t, pre, pos);
    
    ppc->f();
}


void sample_using_mutex()
{
    cout << "\nSample using a mutex:\n";
    Test t;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    
    PreMutex pre(&mutex);
    PosMutex pos(&mutex);
    
    PrePosCaller<Test* const, PreMutex, PosMutex> ppc(&t, pre, pos);
    
    ppc->f();
}


void sample_using_mutex_and_print()
{
    cout << "\nSample using both a mutex and printing:\n";
    Test t;

    PrePosPrinter pre_print("pre"), pos_print("pos");
    
    typedef PrePosCaller<Test* const, PrePosPrinter, PrePosPrinter> PPC_Printer;
    
    PPC_Printer ppc_printer(&t, pre_print, pos_print);

    
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    PreMutex preMutex(&mutex);
    PosMutex posMutex(&mutex);
    
    PrePosCaller<PPC_Printer, PreMutex, PosMutex> ppc(ppc_printer, preMutex, posMutex);
    
    ppc->f();
}

int main()
{
    sample_using_print();
    
    sample_using_mutex();
    
    sample_using_mutex_and_print();    
    
    return 0;
}
