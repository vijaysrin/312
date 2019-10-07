/*
 * Set ADT
 * Project5.c 
 *
 * My Name
 * My Section Time
 * Spring 2017
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way. 
 * Please NOTE, you are responsible for ensuring that the functions work correctly in 
 * your project solution. Just because the function works correctly in my solution does 
 * NOT mean that the function will work correctly in yours. 
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that 
 * the amount of storage available in the elements[] array is equal to length
 */



/* done for you already */
void destroySet(Set* self) {
	free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
	self->len = 0;
	self->elements = 0;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
	self->elements = (int*) malloc(sizeof(int));
	self->elements[0] = x;
	self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
	self->elements = (int*) malloc(other->len * sizeof(int));
	for (int k = 0; k < other->len; k += 1) {
		self->elements[k] = other->elements[k];
	}
	self->len = other->len;	
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
	if (self == other) { return; }
	
	destroySet(self);
	createCopySet(self, other);
}



/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {
	int begin = 0;
	int end = self->len - 1;
	while(begin <= end){
		int middle = (end + begin) / 2;
		if(self->elements[middle] == x)
			return true;
		else if(self->elements[middle] < x)
			begin = middle + 1;
		else
			end = middle - 1;
	}
	return false;
}

int isMemberSetID(const Set* self, int x) {
	int begin = 0;
	int end = self->len - 1;
	while(begin <= end){
		int middle = (end + begin) / 2;
		if(self->elements[middle] == x)
			return middle;
		else if(self->elements[middle] < x)
			begin = middle + 1;
		else
			end = middle - 1;
	}
	return -1;
}



/*
 * add x as a new member to this set. 
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) {
	if(isMemberSet(self, x))
		return;
	//displaySet(self);

	//printf("\n");
	//printf("x: %d\n", x);
	self->elements = (int*) realloc(self->elements, sizeof(int) * (self->len + 1));
	self->elements[self->len] = x;
	self->len++;
	//printf("length: %d\n", self->len);
	
	int location = 0;
	int tmp;
	if(x > self->elements[0]){
		for(int i = 0; i < self->len - 1; i++){
			if(x >= self->elements[i] && x <= self->elements[i + 1]){
				tmp = self->elements[i + 1];

				self->elements[i + 1] = x;
				location = i + 2;
				//printf("The location is: %d\n", location);
				break;
			}
		}
	}
	else{
		location = 1;
		tmp = self->elements[0];
		self->elements[0] = x;
	}

	for(int i = location; i < self->len; i++){
		int tmp2 = self->elements[i];
		self->elements[i] = tmp;
		tmp = tmp2;
		//displaySet(self);
		//printf("tmp: %d\n", tmp);
		//printf("%d\n", self->elements[location]);
	}
	//displaySet(self);
	
}


/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.  
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the 
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array 
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x){
	int z = isMemberSetID(self, x);
	if(z < 0)
		return;
	for(int i = z; i < self->len - 1; i++){
		self->elements[i] = self->elements[i + 1];
	}
	self->len--;
}




void removeSetArray(Set* self, int indexes[], int amount) {
	if(amount == 0)
		return;
	int nextPosition = indexes[0];
	for(int i = 0; i < amount; i++){
		int first = indexes[i] + 1;
		int last = (i == amount - 1)? self->len : indexes[i + 1];
		for(int j = first; j < last; j++){
			self->elements[nextPosition] = self->elements[j];
			nextPosition++;
		}
	}
	self->len -= amount;
}

/* done for you already */
void displaySet(const Set* self) {
	int k;
	
	printf("{");

	if (self->len == 0) { 
		printf("}"); 
	}
	else {
		for (k = 0; k < self->len; k += 1) {
			if (k < self->len - 1) {
				printf("%d,", self->elements[k]);
			} else {
				printf("%d}", self->elements[k]);
			}
		}
	}
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
	if(self->len != other->len)
		return false;
	for(int i = 0; i < self->len; i++){
		if(self->elements[i] != other->elements[i]){
			return false;
		}
	}
	return true;
}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
	if(self->len == 0)
		return true;
	else if(self->len > other->len)
		return false;
	int j = 0;
	for(int i = 0; i < self->len; i++){
		if(self->elements[i] < other->elements[j])
			return false;
		else if(self->elements[i] > other->elements[j]){
			j++;
			i--;
		}
		else
			j++;
	}
	return true;
		
}

/* done for you */
bool isEmptySet(const Set* self) {
	return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {
	//displaySet(&sorted);
	if(other->len == 0)
		self->len = 0;
	int indexes[self->len];
	int amount = 0;

	int j = 0;
	for(int i = 0; i < self->len; i++){
		if(j < other->len - 1){
			if(self->elements[i] < other->elements[j]){
				indexes[amount] = i;
				amount++;
			}
			else if(self->elements[i] > other->elements[j]){
				j++;
				i--;
			}
			else{
				j++;
			}
		}
		else{
			if(self->elements[i] < other->elements[j]){
				indexes[amount] = i;
				amount++;
			}
			else if(self->elements[i] > other->elements[j]){
				for(; i < self->len; i++){
					indexes[amount] = i;
					amount++;
				}
			}
		}
	}
	removeSetArray(self, indexes, amount);
}



/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
	//printf("self->len = %d\n", self->len);
	if(other->len == 0)
		return;
	int indexes[self->len];
	int amount = 0;
	int j = 0;
	for(int i = 0; i < self->len; i++){
		if(j < other->len - 1){
			if(self->elements[i] > other->elements[j]){
				j++;
				i--;
			}
			else if(self->elements[i] == other->elements[j]){
				indexes[amount] = i;
				amount++;
			}
		}
		else{
			if(self->elements[i] == other->elements[j]){
				indexes[amount] = i;
				amount++;
			}
			else if(self->elements[i] > other->elements[j]){
				break;
			}
		}
	}

	removeSetArray(self, indexes, amount);
}

/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {
	Set long1;
	Set short1;

	if(self->len == 0){
		assignSet(self, other);
		return;
	}
	else if(other->len == 0){
		return;
	}
	
	int longer;
	int shorter;
	if(self->len < other->len){
		longer = other->len;
		createCopySet(&long1, other);
		shorter = self->len;
		createCopySet(&short1, self);
	}
	else{
		longer = self->len;
		createCopySet(&long1, self);
		shorter = other->len;
		createCopySet(&short1, other);
	}
	self->elements = (int*)realloc(self->elements, sizeof(int) * (self->len + other->len));
	int j = 0;
	int z = 0;
	for(int i = 0; i < longer; i++){
		if(j < shorter - 1 && i < longer - 1){
			if(long1.elements[i] > short1.elements[j]){
				if(z == self->len)
					self->len++;
				self->elements[z] = short1.elements[j];
				z++;
				j++;
				i--;
			}
			else if(long1.elements[i] < short1.elements[j]){
				if(z == self->len)
					self->len++;
				self->elements[z] = long1.elements[i];
				z++;
			}
			else{
				if(z == self->len)
					self->len++;
				self->elements[z] = long1.elements[i];
				z++;
				j++;
			}
		}
		else if(j == shorter - 1){
			if(long1.elements[i] > short1.elements[j]){
				if(z == self->len)
					self->len++;
				self->elements[z] = short1.elements[j];
				z++;
				for(; i < longer; i++){
					if(z == self->len)
						self->len++;
					self->elements[z] = long1.elements[i];
					z++;
				}
			}
			else if(long1.elements[i] < short1.elements[j]){
				if(z == self->len)
					self->len++;
				self->elements[z] = long1.elements[i];
				z++;
				if(i >= longer - 1){
					self->len++;
					self->elements[z] = short1.elements[j];
				}
			}
			else{
				//printf("length: %d\n", longer);
				for(; i < longer; i++){
					if(z == self->len)
						self->len++;
					self->elements[z] = long1.elements[i];
					z++;
				}
			}
		}
		else{
			if(long1.elements[i] > short1.elements[j]){
				if(z == self->len)
					self->len++;
				self->elements[z] = short1.elements[j];
				j++;
				i--;
				z++;
			}
			else if(long1.elements[i] < short1.elements[j]){
				if(z == self->len)
					self->len++;
				self->elements[z] = long1.elements[i];
				z++;
				for(; j < shorter; j++){
					if(z == self->len)
						self->len++;
					self->elements[z] = short1.elements[j];
					z++;
				}
			}
			else{
				for(; j < shorter; j++){
					if(z == self->len)
						self->len++;
					self->elements[z] = short1.elements[j];
					z++;
				}
			}
		}
	}
	destroySet(&long1);
	destroySet(&short1);
}

