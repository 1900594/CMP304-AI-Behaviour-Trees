#include <LeafNode.h>
#include <FallbackSelector.h>
#include <SequenceSelector.h>
#include <Decorator.h>
#include <Blackboard.h>
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>



BT::NodeStatus leafStandFunction(BT::TreeNode* owner)
{
	if (BT::Blackboard::getInstance()->getAndDeleteValue("disturbance")) {
		return BT::NodeStatus::NODE_FAILURE;
	}

	std::cout << "Standing still..." << std::endl;

	return BT::NodeStatus::NODE_RUNNING;
}

BT::NodeStatus leafPatrolFunction(BT::TreeNode* owner)
{
	if (BT::Blackboard::getInstance()->getAndDeleteValue("disturbance")) {
		return BT::NodeStatus::NODE_FAILURE;
	}

	std::cout << "Patrolling..." << std::endl;

	return BT::NodeStatus::NODE_RUNNING;
}

BT::NodeStatus leafDisturbFunction(BT::TreeNode* owner)
{
	if (BT::Blackboard::getInstance()->getAndDeleteValue("disturbance")) {
		return BT::NodeStatus::NODE_FAILURE;
	}

	std::cout << "Moving towards disturbance..." << std::endl;

	return BT::NodeStatus::NODE_RUNNING;
}

BT::NodeStatus leafExploreFunction(BT::TreeNode* owner)
{
	if (BT::Blackboard::getInstance()->getAndDeleteValue("disturbance")) {
		return BT::NodeStatus::NODE_FAILURE;
	}

	std::cout << "Exploring near disturbance..." << std::endl;

	return BT::NodeStatus::NODE_RUNNING;
}




BT::NodeStatus leafAlarmFunction(BT::TreeNode* owner)
{
	std::cout << "Raising Alarm" << std::endl;

	return BT::NodeStatus::NODE_FAILURE;
}

int main(int argc, char** argv)
{
	//return 0;


	BT::FallbackSelector root("rootNode");
	BT::FallbackSelector branch1("mainBranch");
	BT::LeafNode leafFive("Alarm", leafAlarmFunction);


	//add child nodes to root
	root.addChildNode(&branch1);
	root.addChildNode(&leafFive);

	BT::SequenceSelector guardBranch("guard");
	BT::SequenceSelector exploreBranch("explore");

	branch1.addChildNode(&guardBranch);
	branch1.addChildNode(&exploreBranch);

	BT::Decorator leafDecorOne("timerInsert", 10);
	BT::Decorator leafDecorTwo("timerInsert", 20);
	BT::Decorator leafDecorThree("timerInsert", 5);
	BT::Decorator leafDecorFour("timerInsert", 15);


	guardBranch.addChildNode(&leafDecorOne);
	guardBranch.addChildNode(&leafDecorTwo);
	exploreBranch.addChildNode(&leafDecorThree);
	exploreBranch.addChildNode(&leafDecorFour);


	BT::LeafNode leafOne("Standing", leafStandFunction);
	BT::LeafNode leafTwo("Patrolling", leafPatrolFunction);
	BT::LeafNode leafThree("Disturbance", leafDisturbFunction);
	BT::LeafNode leafFour("Explore", leafExploreFunction);

	leafDecorOne.addChildNode(&leafOne);
	leafDecorTwo.addChildNode(&leafTwo);
	leafDecorThree.addChildNode(&leafThree);
	leafDecorFour.addChildNode(&leafFour);

	while (true)
	{
		if (_kbhit())
		{
			_getch();

			std::cout << "Guard hears a disturbance!" << std::endl;
			BT::Blackboard::getInstance()->addNewValue("disturbance", 1);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));

		}

		/*
		Add remaining code here 
		*/

		BT::NodeStatus result = root.tick();

		if (result == BT::NodeStatus::NODE_SUCCESS)
		{
			root.reset();

		}
		else if (result == BT::NodeStatus::NODE_FAILURE)
		{
			break;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}



}