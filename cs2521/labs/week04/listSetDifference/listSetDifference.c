#include "list.h"


List listSetDifference(List l1, List l2) {
	List different_list = newList();
	Node t = different_list->head;
	Node temp_1 = l1->head;
	Node temp_2 = l2->head;
	for (temp_1 = l1->head; temp_1 != NULL; temp_1 = temp_1->next) {
		int temp_value = temp_1->value;
		int counter = 0;
		for (temp_2 = l2->head; temp_2 != NULL; temp_2 = temp_2->next) {
			if (temp_value == temp_2->value) {
				counter++;
			}
		}
		if (counter == 0) {
			if (t == NULL) {
				Node n = newNode(temp_value);
				different_list->head = n;
				t = n;
			} else {
				Node n = newNode(temp_value);
				t->next = n;
				t = n;
			}
		}
	}
	return different_list;
}
