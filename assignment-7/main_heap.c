/*
	file: main_heap.c
	Heap test file
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dynamicArray.h"

/*
	printTestResult: function to print the result of a test function
	param1: predicate - the result of the test
	param2: nameTestFunction - name of the function being tested
	param3: message - message passed to the test function
	post: result is printed to standard output
*/
void printTestResult(int predicate, char *nameTestFunction, char *message) {
	if (predicate) {
	   printf("%s() - %s: PASS\n",nameTestFunction, message);
	} else {
	   printf("%s() - %s: FAIL\n",nameTestFunction, message);
	}
}

/*
	createTask: create a task from the description and the priority
	param: priority - priority of the task
	param: desc - pointer to the description string
	pre: none
	post: none
	return: a task with description and priority
*/
struct task createTask(int priority, char *desc) {
	struct task newTask;
	newTask.priority = priority;
	strcpy(newTask.description, desc);
	return newTask;
}

/*
	printTask: Display the information about the first node in the heap (root)
	param: task - the task to print
	pre: heap is not empty
	post: no changes to the heap
	return: the task priority and description are printed to standard output
	format: "Priority: XX - Description: Ipsum Lorem"
*/
void printTask(TYPE task) {
	printf("Priority: %d - Description: %s \n",task.priority, task.description);
}

/*
	printList: Display the information about the tasks in ascending order
	param: heap - the heap full of tasks to print
	pre: heap is not empty
	post: no changes to the heap
	return: the task priority and description are printed to standard output
	format: "Priority: XX - Description: Ipsum Lorem" - use the printTask function
*/
void printList(struct DynArr *heap) {
	/* FIXME */
	
	
}

int main() {
	struct task task1, task2, task3, task4, task5, task6, task7, task8, task9, task10;
	struct DynArr *taskList = malloc(sizeof(struct DynArr));
	initDynArr(taskList, 16);

	/* create tasks */
	task1 = createTask(10, "Clean house");
	task2 = createTask(6, "Eat dinner");
	task3 = createTask(2, "Do laundry");
	task4 = createTask(4, "Do dishes");
	task5 = createTask(5, "Grocery shopping");
	task6 = createTask(7, "Change oil");
	task7 = createTask(13, "Do taxes");
	task8 = createTask(8, "Sleep");
	task9 = createTask(1, "Do other homework");
	task10 = createTask(0, "Finish heap homework");

    printf("Beginning testing... \n");

    printf("------------------Testing addHeap------------------ \n");
	/* add tasks to the dynamic array - first three inserts are tested*/
	printf("Add 10 to heap\n");
	addHeap(taskList, task1);
	printTestResult(getDynArr(taskList, 0).priority == 10, "getDynArr", "Priority of index(0) == 10");
	printf("Add 6 to heap\n");
	addHeap(taskList, task2);
	printTestResult(getDynArr(taskList, 0).priority == 6, "getDynArr", "Priority of index(0) == 6");
	printTestResult(getDynArr(taskList, 1).priority == 10, "getDynArr", "Priority of index(1) == 10");
	printf("Add 2 to heap\n");
	addHeap(taskList, task3);
	printTestResult(getDynArr(taskList, 0).priority == 2, "getDynArr", "Priority of index(0) == 2");
	printTestResult(getDynArr(taskList, 1).priority == 10, "getDynArr", "Priority of index(1) == 10");
	printTestResult(getDynArr(taskList, 2).priority == 6, "getDynArr", "Priority of index(2) == 6");
	/* It is your job to test past this point*/
	addHeap(taskList, task4);
	addHeap(taskList, task5);
	addHeap(taskList, task6);
	addHeap(taskList, task7);
	addHeap(taskList, task8);
	addHeap(taskList, task9);
	addHeap(taskList, task10);

	printf("------------------Testing size------------------ \n");
	/* Should print: heap size: 10 */
	printTestResult(sizeDynArr(taskList) == 10, "sizeDynArr", "Size == 10");

	printf("--------------printing heap-------------- \n");
	/* Should print - 0 1 6 4 2 7 13 10 8 5 (with descriptions) */
	printList(taskList);

	printf("------------------Testing getMinHeap------------------ \n");
	printTestResult(getMinHeap(taskList).priority == 0, "getMinHeap", "Priority == 0");

	printf("------------------Testing removeMinHeap------------------ \n");
	removeMinHeap(taskList);
	printTestResult(getMinHeap(taskList).priority == 1, "getMinHeap", "Priority == 1");
	printTestResult(getDynArr(taskList, 1).priority == 2, "getDynArr", "Priority == 2");
	printTestResult(getDynArr(taskList, 2).priority == 6, "getDynArr", "Priority == 6");
	printTestResult(getDynArr(taskList, 3).priority == 4, "getDynArr", "Priority == 4");
	printTestResult(getDynArr(taskList, 4).priority == 5, "getDynArr", "Priority == 5");
	printTestResult(getDynArr(taskList, 5).priority == 7, "getDynArr", "Priority == 7");
	printTestResult(getDynArr(taskList, 6).priority == 13, "getDynArr", "Priority == 13");
	printTestResult(getDynArr(taskList, 7).priority == 10, "getDynArr", "Priority == 10");
	printTestResult(getDynArr(taskList, 8).priority == 8, "getDynArr", "Priority == 8");
	
	printf("------------------Initial testing complete------------------ \n");
	
	return 0;
}
