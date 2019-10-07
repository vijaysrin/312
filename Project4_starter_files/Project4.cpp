// CRM <Project4.cpp>
// EE 312 Project 4 submission by
// Vijay Srinivasan
// vks445
// Slip days used: <0>
// Spring 2018


#include <stdio.h>
#include <assert.h>
#include "MyString.h"
#include "MyString.cpp"
#include "Invent.h"


#define MAX_CUSTOMERS 1000
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;

static Customer INVENTORY;

/* you'll probably need several more global variables */
/* and of course, you have a few functions to write */



int checkType(String* word){
  String BOTTLES = StringCreate("Bottles");
  String DIAPERS = StringCreate("Diapers");
  String RATTLES = StringCreate("Rattles");
  int result = 0;
  if(StringIsEqualTo(word, &BOTTLES)){
    result =  1;
  }
  else if(StringIsEqualTo(word, &DIAPERS)){
    result = 2;
  }
  else if(StringIsEqualTo(word, &RATTLES)){
    result = 3;
  }
  StringDestroy(&BOTTLES);
  StringDestroy(&DIAPERS);
  StringDestroy(&RATTLES);
  return result;
}

int checkName(String* name){
  for(int i = 0; i < num_customers; i++){
    if(StringIsEqualTo(name, &customers[i].name)){
       return i;
      }
  }
  return -1;
}

void getMaxBottles(){
  int max = 0;
  int ID = 0;
  for(int i = 0; i < num_customers; i++){
    if(customers[i].bottles > max){
      max = customers[i].bottles;
      ID = i;
    }
  }
  if(max == 0)
    printf("no one has purchased any Bottles\n");
  else{
    StringPrint(&customers[ID].name);
    printf(" has purchased the most Bottles (%d)\n", max);
  }
}

void getMaxDiapers(){
  int max = 0;
  int ID = 0;
  for(int i = 0; i < num_customers; i++){
    if(customers[i].diapers > max){
      max = customers[i].diapers;
      ID = i;
    }
  }
  if(max == 0)
    printf("no one has purchased any Diapers\n");
  else{
    StringPrint(&customers[ID].name);
    printf(" has purchased the most Diapers (%d)\n", max);
  }
}

void getMaxRattles(){
  int max = 0;
  int ID = 0;
  for(int i = 0; i < num_customers; i++){
    if(customers[i].rattles > max){
      max = customers[i].rattles;
      ID = i;
    }
  }
  if(max == 0)
    printf("no one has purchased any Rattles\n");
  else{
    StringPrint(&customers[ID].name);
    printf(" has purchased the most Rattles (%d)\n", max);
  }
}


/* clear the inventory and reset the customer database to empty */
void reset(void) {
  for(int i = 0; i < num_customers; i++){
    StringDestroy(&customers[i].name);
    customers[i].bottles = 0;
    customers[i].diapers = 0;
    customers[i].rattles = 0;
  }
  num_customers = 0;
  INVENTORY.bottles = 0;
  INVENTORY.diapers = 0;
  INVENTORY.rattles = 0;
  
}

void processSummarize() {
  printf("There are %d Bottles, %d Diapers and %d Rattles in inventory\n", INVENTORY.bottles, INVENTORY.diapers, INVENTORY.rattles);
  printf("we have had a total of %d different customers\n", num_customers);
  getMaxBottles();
  getMaxDiapers();
  getMaxRattles();
  
}

void processPurchase() {
  String product;
  int amount;
  readString(&customers[num_customers].name);
  int custom = checkName(&customers[num_customers].name);
  readString(&product);
  readNum(&amount);
  
  if(custom < 0){
    custom = num_customers;
    customers[custom].bottles = 0;
    customers[custom].diapers = 0;
    customers[custom].rattles = 0;
    num_customers++; 
  }
  else{
    StringDestroy(&customers[num_customers].name);
  }
  
  switch(checkType(&product)){
      case 0:
          printf("Invalid product");
          break;

      case 1:
          if(amount > INVENTORY.bottles){
            printf("Sorry ");
            StringPrint(&customers[custom].name);
            printf(", we only have %d Bottles\n", INVENTORY.bottles);
            if((custom == num_customers - 1)&&(customers[custom].diapers == 0)&&(customers[custom].rattles == 0)){
              StringDestroy(&customers[custom].name);
              num_customers--;
            }
            break;
          }
          INVENTORY.bottles -= amount;
          customers[custom].bottles += amount;
          break;

      case 2:
          if(amount > INVENTORY.diapers){
            printf("Sorry ");
            StringPrint(&customers[custom].name);
            printf(", we only have %d Diapers\n", INVENTORY.diapers);
            if((custom == num_customers - 1)&&(customers[custom].bottles == 0)&&(customers[custom].rattles == 0)){
              StringDestroy(&customers[custom].name);
              num_customers--;
            }
            break;
          }
          INVENTORY.diapers -= amount;
          customers[custom].diapers += amount;
          break;

      case 3:
          if(amount > INVENTORY.rattles){
            printf("Sorry ");
            StringPrint(&customers[custom].name);
            printf(", we only have %d Rattles\n", INVENTORY.rattles);
            if((custom == num_customers - 1)&&(customers[custom].diapers == 0)&&(customers[custom].bottles == 0)){
              StringDestroy(&customers[custom].name);
              num_customers--;
            }
            break;
          }
          INVENTORY.rattles -= amount;
          customers[custom].rattles += amount;
          break;
        }
  StringDestroy(&product);
  

}

void processInventory() {
  String next_command;
  int amount;
  readString(&next_command);
  readNum(&amount);
  switch(checkType(&next_command)){
    case 0:
      printf("Invalid inventory term");
      break;

    case 1:
      INVENTORY.bottles += amount;
      break;

    case 2:
      INVENTORY.diapers += amount;
      break;

    case 3:
      INVENTORY.rattles += amount;
      break;
  }
  StringDestroy(&next_command);

  
}
