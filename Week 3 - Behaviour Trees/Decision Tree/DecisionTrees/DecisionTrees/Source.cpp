#include "Node.h"
#include <iostream>
#include <thread>
using namespace std::chrono_literals;

int main()
{
	srand(time(NULL));

	// Create functions / lambdas for each unique node in the tree

	auto root_node_random = []()->int {
		int random = rand() % 100;
		if (random < 40) {
			return 0;
		}
		else if (random >= 40 && random <= 60) {
			return 1;
		}
		else {
			return 2;
		}
	};


	auto leaf_node_1 = []()->int {
		std::cout << "Leaf node 1 has been called." << std::endl;
		return 0;
	};


	auto leaf_node_2 = []()->int {
		std::cout << "Leaf node 2 has been called." << std::endl;
		return 0;
	};

	auto leaf_node_3 = []()->int {
		std::cout << "Leaf node 3 has been called." << std::endl;
		return 0;
	};
	// Create instances of deciusion nodes and leaf nodes as appropriate
	DecisionNode root_node(root_node_random);
	Node leaf1(leaf_node_1);
	Node leaf2(leaf_node_2);
	Node leaf3(leaf_node_3);

	// Add the leaf nodes as children to the connected decision nodes
	root_node.addChildNode(&leaf1);
	root_node.addChildNode(&leaf2);
	root_node.addChildNode(&leaf3);

	// Run the root node of the tree
	while (true)
	{	
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		root_node.run();
	}



	
}