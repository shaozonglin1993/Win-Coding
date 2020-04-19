#include <iostream>

using namespace std;

namespace TJVictor.DesignPattern.SubscribePublish
{
	//定义订阅事件
	public delegate void SubscribeHandle(string str);

	//定义订阅接口
	public interface ISubscribe
	{
		event SubscribeHandle SubscribeEvent;
	}
}


/*
namespace first
{
	int a;
	int b;
}

int main()
{
	cout << first::a << endl;
	cout << first::b << endl;
}
*/