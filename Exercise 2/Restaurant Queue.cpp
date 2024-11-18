#include <iostream>
#include <queue>
#include <fstream>
#include <string>
using namespace std;

// Define the structure for the order information
struct Order
{
	int arrive_time; int dur;
};
// make a queue to store orders
queue<Order> orders;
// Define the structure for the restaurant
struct res {

	int N; //Num of orders
	int T; // closing time
	// Function to read input and store orders
	void input(const string& filename) {
		fstream file("abd.txt");
		if (file.is_open()) {
			file >> N >> T;
			for (int i = 0; i < N; i++) {
				int t;
				int d;
				file >> t >> d;
				Order order = { t,d };
				orders.push(order);
			}
			file.close();
		}
		else {
			cerr << "Unable to open the file." << endl;
		}
	}// Function to process and print order information
	void prorder() {
		int time = 0;
		int max_dur = 0;
		bool late = false;
		// Iterate through all the orders
		for (int i = 0; i < N; i++) {
			Order order = orders.front();
			orders.pop();
			// Check if the chef can take a break before the next order
			if (time < order.arrive_time) {
				cout << "Chef has a break: " << time << " to " << order.arrive_time << endl;
				time = order.arrive_time; // Update the current time to the next order's arrival time
			}  // Update the current time with the order duration
			time += order.dur;
			// Update the maximum order duration
			if (order.dur > max_dur) {
				max_dur = order.dur;
			}
			// Calculate expected and actual completion times
			int expected_completion_time = order.arrive_time + order.dur;
			int actual_completion_time = time;
			// Print order information
			cout << "Order " << (i + 1) << ": expected completion time = " << expected_completion_time
				<< ", actual completion time = " << actual_completion_time << ";" << endl;
			if (actual_completion_time > T) {
				late = true;
			}

		}
		// Print the maximum order duration and completion status
		cout << "the max duration:" << max_dur << "  ";
		if (late) {
			cout << "there are orders which are not completed or the chef finished them after time " << T;
		}
		else {
			cout << "they are completed";
		}
	}
};
int main() {

	res restaurant;
	restaurant.input("abd.txt");
	restaurant.prorder();
	return 0;
}