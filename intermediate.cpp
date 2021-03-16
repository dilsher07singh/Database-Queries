//
//  intermediate.cpp
//  assign1main
//
//  Created by Dilsher Singh on 19/03/20.
//  Copyright © 2020 Dilsher Singh. All rights reserved.
//

#include <iostream>
#include "intermediate.h"
#include "table.h"

Intermediate::Intermediate(const Table &table){
    attrs=table.attrs;
    numAttrs=table.numAttrs;
    if(table.numEntries==0){
        head=nullptr;
        tail=nullptr;
    }
    else{
    EntryNode*n;
    n=new EntryNode;
    n->entry=table.entries[0];
    n->prev=nullptr;
    head=n;
    tail=n;
    
    for(int i=1;i<table.numEntries;i++){
    n=new EntryNode;
    n->entry=table.entries[i];
    n->prev=tail;
    tail->next=n;
    tail=n;
    }
    tail->next=nullptr;
    }
}
    

Intermediate::~Intermediate(){
    EntryNode*temp=head;
    int count=0;
    while(temp !=nullptr){
        count++;
        temp=temp->next;
    }
    for(int i=1;i<count;i++){
        EntryNode*p=tail;
        tail=tail->prev;
        tail->next=nullptr;
        p->prev=nullptr;
        delete p;
            p=nullptr;
        }
    delete head;
    
  
}

Intermediate& Intermediate:: where(const string &attr, enum compare mode, const string &value){
   int x=-1;
   int count=0;
   int count1=0;
   for(int i=0;i<numAttrs;i++){
       if(attrs[i]==attr){
           x=i;
       }
   }
    if(x==-1)
        return (*this);
    EntryNode*temp=head;
    EntryNode*check=head;
   if(mode==EQ){
    while(temp!=nullptr){
        if(temp->entry[x] == value){
            check->entry=temp->entry;
            check=check->next;
            count1++;
        }
        count++;
        temp=temp->next;
    }
       
       for(int i=count;i>count1;i--){
       EntryNode*p=tail;
           if(i!=1){
       tail=tail->prev;
       tail->next=nullptr;
       p->prev=nullptr;
           }
       delete p;
           p=nullptr;
           if(i==1){
             head=nullptr;
               tail=nullptr;
           }
       }

   }
   else if(mode==CONTAINS){
       while (temp!=nullptr){
           /*
           int pos=0;
           int index;
           if((index = value.find(temp->entry[x], pos) != std::string::npos)){
            */
           if(temp->entry[x].find(value)!=std::string::npos){
               check->entry=temp->entry;
               check=check->next;
               count1++;
           }
           count++;
           temp=temp->next;
       }
     
       for(int i=count;i>count1;i--){
       EntryNode*p=tail;
           if(i!=1){
       tail=tail->prev;
       tail->next=nullptr;
           }
       p->prev=nullptr;
       delete p;
           p=nullptr;
           if(i==1){
               head=nullptr;
               tail=nullptr;
           }
       }
       
   }
    return (*this);

}

Intermediate& Intermediate:: orderBy(const string &attr, enum order order){
    int x=-1;
    int count=0;
    int z=0;
    for(int i=0;i<numAttrs;i++){
    if(attrs[i]==attr){
        x=i;
    }
        
    }
        if(x==-1)
            return (*this);
        EntryNode*temp=head;
    while(temp!=nullptr){
        count++;
        temp=temp->next;
    }
    string *a=new string[count];
    string temper;
    EntryNode*createlist=head;
    while(createlist !=nullptr){
        a[z]=createlist->entry[x];
        z++;
        createlist=createlist->next;
    }
    string**c=new string *[count];
    EntryNode*ctem=head;
    int g=0;
    while (ctem !=nullptr){
        c[g]=ctem->entry;
        g++;
        ctem=ctem->next;
    }
     
    if(order==ASCENDING){
        for (int j = 0 ; j < (count - 1); j++){
                for (int i=j+1 ; i<count; i++){
                    if(a[j].compare(a[i])>0){
                        temper=a[j];
                        a[j]=a[i];
                        a[i]=temper;
                    }
                }
        }
        EntryNode*main=head;
        int y=0;
        while(main !=nullptr){

            for(int i=0;i<count;i++){
            if(c[i][x]==a[y]){
                    main->entry=c[i];
                main=main->next;

                y++;
        
            }
        }
        }
        
    }
        
    
    else if(order==DESCENDING){
        for (int j = 0 ; j < (count - 1); j++){
                    for (int i=j+1 ; i<count; i++){
                        if(a[j].compare(a[i])>0){
                            temper=a[j];
                            a[j]=a[i];
                            a[i]=temper;
                        }
                    }
            }
            EntryNode*main=head;
            int y=count-1;
            while(main !=nullptr){

                for(int i=0;i<count;i++){
                if(c[i][x]==a[y]){
                        main->entry=c[i];
                    main=main->next;

                    y--;
            
                }
            }
            }
            
        }
    delete []a;
    delete []c;
    return (*this);

    }
        
        

 


Intermediate& Intermediate::limit(unsigned int limit){
    int x = 0;
    EntryNode*temp=head;
    while(temp!=nullptr){
        x++;
        temp=temp->next;
    }
    if(limit==0){
        for(int i=x;i>0;i--){
              EntryNode*p=tail;
            if(i !=1){
              tail=tail->prev;
              tail->next=nullptr;
           }
              p->prev=nullptr;
              delete p;
                  p=nullptr;
           if(i==1){
                head=nullptr;
                tail=nullptr;
           }
              }
    }
    else{
        for(int i=x;i>limit;i--){
        EntryNode*p=tail;
        tail=tail->prev;
        tail->next=nullptr;
        p->prev=nullptr;
        delete p;
            p=nullptr;
        }
    }
    
    return (*this);
}



void Intermediate::select (const string *attrs, int numAttrs)const {
    EntryNode*he=head;
    if(he==nullptr){
        if(numAttrs>0){
            for(int i=0;i<numAttrs;i++){
                if(i==numAttrs-1)
                    cout<<attrs[i];
                else
            cout<<attrs[i]<<" | ";
            }
            cout<<endl;
        }
        else{
            for(int i=0;i<this->numAttrs;i++){
                if(i==this->numAttrs-1)
                cout<<this->attrs[i];
                else
            cout<<this->attrs[i]<<" | ";
            }
        cout<<endl;
        }

    }
    
    else if(attrs==nullptr){
        int *p=new int[this->numAttrs];
        for(int i=0;i<this->numAttrs;i++){
            int max=this->attrs[i].size();
            EntryNode*temp=head;
            while(temp!=nullptr){
                if(max<temp->entry[i].size())
                max=temp->entry[i].size();
                temp=temp->next;
                p[i]=max;
            }
            
        }
        for(int i=0;i<this->numAttrs;i++){
            if(i==this->numAttrs-1)
            cout<<_left_pad_until(this->attrs[i], p[i]);
            else
            cout<<_left_pad_until(this->attrs[i], p[i])<<" | ";
            
        }
        cout<<endl;
        EntryNode*temp=head;
        while(temp!=nullptr){
            for(int i=0;i<this->numAttrs;i++){
                if(i==this->numAttrs-1)
                cout<<_left_pad_until(temp->entry[i], p[i]);
                else if(temp->entry!=nullptr)
                cout<<_left_pad_until(temp->entry[i], p[i])<<" | ";
            }
                cout<<endl;
            temp=temp->next;
}
        delete [] p;
}
    
    else if(attrs!=nullptr && numAttrs>0){
        
        int *a=new int[numAttrs];
        int y=0;
        int *p=new int[numAttrs];

        for(int i=0;i<numAttrs;i++){
            for(int j=0;j<this->numAttrs;j++){
                if(this->attrs[j]==attrs[i]){
                    int max=this->attrs[j].size();
                    EntryNode*temp=head;
                    while(temp!=nullptr){
                        if(max<temp->entry[j].size())
                        max=temp->entry[j].size();
                        temp=temp->next;
                        p[i]=max;
                        
                    }
                    if(i==numAttrs-1)
                    cout<<_left_pad_until(this->attrs[j], p[i]);
                    else
                    cout<<_left_pad_until(this->attrs[j], p[i])<<" | ";
                    a[y]=j;
                    y++;
                }
                 
            }
                
        }
        cout<<endl;
        EntryNode*temp=head;
        while(temp!=nullptr){
            for(int i=0;i<numAttrs;i++){
                if(i==numAttrs-1)
                    cout<<_left_pad_until(temp->entry[a[i]],p[i]);
                else
            cout<<_left_pad_until(temp->entry[a[i]],p[i])<<" | ";
            }
            cout<<endl;
        temp=temp->next;
            

        }
        delete[] a;
        delete[] p;
        }
    
}

void Intermediate:: update(const string &attr, const string &new_value) const{
    int x=-1;
    for(int i=0;i<numAttrs;i++){
    if(attrs[i]==attr)
        x=i;
    }
    if(x>=0){
        EntryNode*temp=head;
        while(temp!=nullptr){
            temp->entry[x]=new_value;
            temp=temp->next;
        }
        
        
        
    }
}

