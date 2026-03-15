// email: fin090043@gmail.com#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

// ------ Creaet a patient struct ------
typedef struct patient{
    char name[20];
    int age;
    char address[100];
    int reg;
    int priority;
}p_t;

// ----- Create a heap struct ------
typedef struct heap{
    p_t list[SIZE];
    int next;
}h_t;

// ----- Swap function -----
void swap(p_t* p1, p_t* p2){
    p_t temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
    return;
}

// ----- Initiate a max heap -----
void init_heap(h_t* hp){
    hp->next = 0;
    return;
}

// ----- Boolean function to check the waiting list status ------
bool is_empty(h_t* hp){
    if(hp->next<=0){
        return true;
    }
    return false;
}

bool is_full(h_t* hp){
    if(hp->next>=SIZE){
        return true;
    }
    return false;
}

// ------ Int function for heapify calculation ------
int parent(int idx){
    if(idx>=0 && idx<SIZE){
        return (idx-1)/2;
    }
    return -1;
}

int left_child(int idx){
    if(idx>=0 && idx<SIZE){
        return idx*2 + 1;
    }
    return -1;
}

int right_child(int idx){
    if(idx>=0 && idx<SIZE){
        return idx*2 + 2;
    }
    return -1;
}

// ----- Node validation -----
bool is_null(h_t* hp, int idx){
    if(idx>=hp->next){
        return true;
    }
    return false;
}

bool is_valid(h_t* hp, int idx){
    if ((0 <= idx) && (idx < SIZE) && (idx < hp->next)){
        return true;
    } 
    return false;
}

// ----- Heapify calculation -----
void rebalance_up(h_t* hp, int idx){
    if(idx==0){
        return;
    }

    if(!is_valid(hp, idx)){
        printf("Invalid Node\n");
        return;
    }

    int p = parent(idx);
    p_t* parent_patient = &(hp->list[p]);
    p_t* this_patient = &(hp->list[idx]);

    if(this_patient->priority > parent_patient->priority){
        swap(this_patient, parent_patient);
        rebalance_up(hp, p);
    }
    return;
}

void rebalance_down(h_t* hp, int idx){
    if(!is_valid(hp, idx)){
        printf("Invalid Node\n");
        return;
    }

    int left = left_child(idx);
    int right = right_child(idx);
    p_t* this_patient = &(hp->list[idx]);
    p_t* left_patient = &(hp->list[left]);
    p_t* right_patient = &(hp->list[right]);

    if(is_null(hp, left)){
        return;
    }

    if(is_null(hp, right)){
        if(left_patient->priority > this_patient->priority){
            swap(left_patient, this_patient);
        }
        return;
    }

    if(left_patient->priority > right_patient->priority && left_patient->priority > this_patient->priority){
        swap(left_patient, this_patient);
        rebalance_down(hp, left);
    }else if(right_patient->priority > left_patient->priority && right_patient->priority > this_patient->priority){
        swap(right_patient, this_patient);
        rebalance_down(hp, right);
    }
    return;
}

// ----- Data modification ----
void insert(h_t* hp){
    if(is_full(hp)){
        printf("PATIENT LIST IS FULL!\n");
        return;
    }
    p_t patient;
    printf("Enter patient Name:");
    scanf("%s", patient.name);
    printf("Enter the patient's age:");
    scanf("%d", &patient.age);
    printf("Enter the address:");
    scanf("%s", patient.address);
    printf("Enter the reg no:");
    scanf("%d", &patient.reg);
    printf("Enter the priority:");
    scanf("%d", &patient.priority);

    if(is_empty(hp)){
        hp->list[hp->next] = patient;
        hp->next++;
        return;
    }
    hp->list[hp->next] = patient;
    hp->next++;
    rebalance_up(hp, hp->next-1);


}

void delete(h_t* hp){
    if(is_empty(hp)){
        hp->next = 0;
        printf("\n\t\t\t***PATIENT LIST IS EMPTY!***\n\n");
        return;
    }
    p_t result = hp->list[0];
    hp->list[0] = hp->list[hp->next-1];
    (hp->next) --;
    rebalance_down(hp, 0);
    printf("\n\t\t\t***The Following patient has been removed:***\n");
    printf("\t\t\t\tThe name of patient is:%s\n", result.name);
    printf("\t\t\t\tThe age of patient is:%d\n", result.age);
    printf("\t\t\t\tThe address of patient is : %s\n\n", result.address);

    return;
}

// ----- Show current waiting list of patient -----
void display(h_t* hp) {
    if (is_empty(hp)) {
        printf("\nTHERE IS NO PATIENT");
    } else {
        printf("\nPriority wise appointments are:\n");
        for(int i=0; i<hp->next; i++) {
        printf("The name of patient is:%s\n", hp->list[i].name);
        printf("The age of patient is:%d\n", hp->list[i].age);
        printf("The address of patient is : %s\n", hp->list[i].address);
        printf("---------------------------------------------------\n");
        }
    }
    return;
}


// Main program
int main() {
    h_t max_heap;
    init_heap(&max_heap);
    int option;
    do{
        printf("\t\t\t Hospital emergency room system\n");
        printf("\t\t\t1.ADD A PATIENT\n");
        printf("\t\t\t2.DELETE A RECORD\n");
        printf("\t\t\t3.PATIENTS WAITING IN THE QUEUE\n");
        printf("\t\t\t4.Exit\n");
        printf("\t\t\tEnter your choice:");
        scanf("%d", &option);
        switch (option) {
            // Select 1 to insert elements in the priority queue
            case 1:
                insert(&max_heap);
                break;
            // Select 2 to delete the elements at the front of priority queue
            case 2:
                delete(&max_heap);
                break;
            // Select 3 To display the elements present in the priority queue
            case 3:
                display(&max_heap);
                break;
            // Select 4 to terminate
            case 4:
                printf("The program is being terminated\n");
                break;
        }
    } while (option != 4);
    return 0;
}
