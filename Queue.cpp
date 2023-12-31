#include "Queue.h"
Queue::Queue() { }
Queue::~Queue() { }


bool Queue::isEmpty() {
	return (frontNode == nullptr);
}




bool Queue::enqueue(Item item) {
	Node* newNode = new Node;

	newNode->item = item;

	newNode->next = nullptr;

	if (isEmpty()) {

		frontNode = newNode;
		backNode = newNode;

		// don't need to set newNode->next to frontNode becuase frontNode is nullptr anyway.

	}

	else {

		backNode->next = newNode;

		backNode = newNode;

	}

	return true;
}

bool Queue::dequeue(Item& item) {
	if (isEmpty()) {
		std::cout << "Queue is empty" << std::endl;
		return false;
	}

	else {
		Node* temp = frontNode;

		item = temp->item;

		if (frontNode == backNode) {
			frontNode = nullptr;
			backNode = nullptr;

		}

		else {
			frontNode = frontNode->next;

		}

		temp->next = nullptr;
		delete temp;

	}
	return true;

}

Order Queue::getFront(/*Item& item*/) {
	if (isEmpty()) {
		std::cout << "Queue is empty" << std::endl;
		return Order();
	}

	else {
		Order item = frontNode->item;
		return item;
	}
}

int Queue::getLength()
{
	int length = 0;
    Node* current = frontNode;

    while (current != nullptr) {
        length++;
        current = current->next;
    }

    return length;

}

void Queue::displayItems() {
	if (isEmpty()) {
		std::cout << "Queue is empty" << std::endl;
		return;
	}

	Node* current = frontNode;
	while (current != nullptr) {
		// Assuming Order class has orderId and customerName members
		std::cout << "Customer: "  << current->item.getCustName() << ", Charge: " << current->item.getCharge() << std::endl;
		current = current->next;
	}
}