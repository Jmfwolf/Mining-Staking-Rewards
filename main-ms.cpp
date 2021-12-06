#include <iostream>
#include <vector>
#include <string>

struct stake {
	int timeleft;
	double asset;
};
void day_count(::std::vector<stake>& vec, double& total, const int& interval, const int& lock, const int& min, const double& apr, const double& mine);

int main()
{
	double stake_min;
	double daily_mining_reward;
	double total;
	double apr;

	int stake_reward_interval;
    int dur_in_days;
	int lockup_time;
	char ans;
	::std::vector<stake> staking;

	::std::cout << "How much do you have of the asset that is not staking?\n";
	::std::cin >> total;
	::std::cout << "What is the minimum staking requirement?\n";
	::std::cin >> stake_min;
	::std::cout << "What is the annual reward rate?\n";
	::std::cin >> apr;
	::std::cout << "\nWhat are your daily mining rewards?\n";
	::std::cin >> daily_mining_reward;
	::std::cout << "\nHow often, in days, do are your staking rewards paid?\n";
	::std::cin >> stake_reward_interval;
	::std::cout << "\nHow long is the lock up period, in days, for staking?\n";
	::std::cin >> lockup_time;
	::std::cout << "\nHow long, in days, will you auto-reinvest?\n";
	::std::cin >> dur_in_days;
	::std::cout << "\nDo you have any assets staking now? (y/n)\n";
	::std::cin >> ans;
	while (ans == 'y')
	{
		stake first;
		::std::cout << "How much of the asset is staking?\n";
		::std::cin >> first.asset;
		::std::cout << "How much time is left?\n";
		::std::cin >> first.timeleft;
		
		staking.push_back(first);
		::std::cout << "Would you like to add another asset? (y/n)\n";
		::std::cin >> ans;
	}
	for (; dur_in_days > 0; dur_in_days--)
	{
		day_count(staking, total, stake_reward_interval, lockup_time, stake_min, apr, daily_mining_reward);
	}
	while (!staking.empty())
	{
		total += staking[0].asset;
		staking.erase(staking.begin());
	}
	::std::cout << "At the end of your duration, you will have: " << total << "\n";

}


void day_count(::std::vector<stake>& vec, double& total, const int& interval, const int& lock, const int& min, const double& apr, const double& mine)
{
	total += mine;
	for (int i = 0; i < vec.size(); i++)
	{
		vec[i].timeleft--;
		if ((lock - vec[i].timeleft) % interval == 0)
		{
			double hold = (vec[i].asset * (apr / 100 / (365 / interval)));
			total += hold;
		}
		if (vec[i].timeleft <= 0)
		{
			total += vec[i].asset;
			vec.erase(vec.begin() + i);
			i--;
		}
	}
	if (total >= min)
	{
		stake reinvest;
		reinvest.asset = total;
		reinvest.timeleft = lock;
		total = 0;
		vec.push_back(reinvest);
	}
}
