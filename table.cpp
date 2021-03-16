//
//  table.cpp
//  assign1main
//
//  Created by Dilsher Singh on 19/03/20.
//  Copyright © 2020 Dilsher Singh. All rights reserved.
//
#include "table.h"

Table::Table(){
    numAttrs=0;
    numEntries=0;
    attrs=nullptr;
    entries=nullptr;
    
}
Table::Table(const Table &another){
    numAttrs=another.numAttrs;
    numEntries=another.numEntries;
    attrs=new string[another.numAttrs];
    for(int i=0;i<another.numAttrs;i++)
    attrs[i]=another.attrs[i];
    entries=new string*[another.numEntries];
    for(int i=0;i<another.numEntries;++i)
        entries[i]=new string[another.numAttrs];
        for(int i=0;i<another.numEntries;i++){
            for(int j=0;j<another.numAttrs;j++)
                entries[i][j]=another.entries[i][j];
                }
    
    }
    

Table::~Table(){
    delete [] attrs;
    for (int i=0;i<numEntries;i++)
        delete []entries[i];
    delete []entries;
}

bool Table::addAttribute(const string &attr,int index,const string &default_value ){
    
    if(index<-1 || index>numAttrs)
        return false;
    
    string*att=new string;
    *att=attr;
    

    string *newarr=new string[numAttrs+1];
    
    if(index>=0 && index<numAttrs){
    for(int i=index;i<numAttrs;i++)
        newarr[i+1]=attrs[i];
      for(int i=0;i<index;i++)
        newarr[i]=attrs[i];
    }
    else{

    for(int i=0;i<numAttrs;i++)
        newarr[i]=attrs[i];
    }
    
    if(index==-1 || index==numAttrs){
    newarr[numAttrs]=*att;
        if(numEntries>0){
                string**entrytemp=new string*[numEntries];
                  for(int j=0;j<numEntries;j++)
                      entrytemp[j]=new string[numAttrs+1];
            
                for(int j=0;j<numEntries;j++){
                   for(int i=0;i<numAttrs;i++)
                       entrytemp[j][i]=entries[j][i];
                    entrytemp[j][numAttrs]=default_value;
                }
                for (int i=0;i<numEntries;i++)
                    delete []entries[i];
                delete []entries;
                entries=entrytemp;

            }
        }
    
    else{
    newarr[index]=*att;
    if(numEntries>0){
            string**entrytemp=new string*[numEntries];
              for(int j=0;j<numEntries;j++)
                  entrytemp[j]=new string[numAttrs+1];
        
        if(index>=0 && index<numAttrs){
            for(int j=0;j<numEntries;j++){
                   for(int i=index;i<numAttrs;i++)
                       entrytemp[j][i+1]=entries[j][i];
                for(int i=0;i<index;i++)
                    entrytemp[j][i]=entries[j][i];
                entrytemp[j][index]=default_value;
                       }
        }
       for (int i=0;i<numEntries;i++)
           delete []entries[i];
       delete []entries;
        entries=entrytemp;
    }
        
    
    }
    numAttrs++;
    delete att;
    delete []attrs;
    attrs=newarr;
    return true;
}
bool Table::addEntry(const string *entry, int index){
    if(index<-1 || index>numEntries)
            return false;
    
    string**entrytemp=new string*[numEntries+1];
    for(int j=0;j<numEntries+1;j++)
        entrytemp[j]=new string[numAttrs];
    
    if(index>=0 && index<numEntries){
        for(int j=index;j<numEntries;j++){
        for(int i=0;i<numAttrs;i++)
            entrytemp[j+1][i]=entries[j][i];
            }
        for(int j=0;j<index;j++){
        for(int i=0;i<numAttrs;i++)
            entrytemp[j][i]=entries[j][i];
            }
    }
    
    else{
    for(int j=0;j<numEntries;j++){
    for(int i=0;i<numAttrs;i++)
        entrytemp[j][i]=entries[j][i];
        }
    }
    
    if(index==-1){
        for(int i=0;i<numAttrs;i++)
            entrytemp[numEntries][i]=entry[i];
    }
    else{
    for(int i=0;i<numAttrs;i++)
        entrytemp[index][i]=entry[i];
    }
    
    
    for (int i=0;i<numEntries;i++)
        delete []entries[i];
    delete []entries;
    entries=entrytemp;
  
    numEntries++;
    return true;
}

bool Table::deleteAttribute(int index){
    if(index<0 || index>numAttrs-1)
        return false;
    numAttrs--;
   string *newarr=new string[numAttrs];
    for(int i=0;i<index;i++)
        newarr[i]=attrs[i];
    for(int j=index;j<numAttrs;j++)
        newarr[j]=attrs[j+1];
        
    if(numEntries>0){
        string**entrytemp=new string*[numEntries];
        for(int j=0;j<numEntries;j++)
            entrytemp[j]=new string[numAttrs];
        
        for(int i=0;i<numEntries;i++){
               for(int j=0;j<index;j++)
                   entrytemp[i][j]=entries[i][j];
           }
           
        for(int i=0;i<numEntries;i++){
               for(int j=index;j<numAttrs;j++)
                   entrytemp[i][j]=entries[i][j+1];
        }

        for (int i=0;i<numEntries;i++)
            delete []entries[i];
        delete []entries;
        entries=entrytemp;
        
    }
    
    delete [] attrs;
    attrs=newarr;
    return true;
}

bool Table::deleteEntry(int index){
    if(index<0 || index>numEntries-1)
    return false;
    numEntries--;
    string**entrytemp=new string*[numEntries];
          for(int j=0;j<numEntries;j++)
              entrytemp[j]=new string[numAttrs];
    
    for(int i=0;i<index;i++){
        for(int j=0;j<numAttrs;j++)
            entrytemp[i][j]=entries[i][j];
    }
    
    for(int i=index;i<numEntries;i++){
        for(int j=0;j<numAttrs;j++)
            entrytemp[i][j]=entries[i+1][j];
    }
    for (int i=0;i<numEntries+1;i++)
        delete []entries[i];
    delete []entries;
    entries=entrytemp;
    return true;
    
}
bool Table::append(const Table &another){
    if(numAttrs!=another.numAttrs)
        return false;
    for(int i=0;i<numAttrs;i++){
        if (attrs[i] !=another.attrs[i])
            return false;
    }
    for(int i=0;i<another.numEntries;i++)
        addEntry(another.entries[i],-1);
        
        
    return true;
}








