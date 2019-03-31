#pragma once
#include <opencv2/core.hpp>
#include <vector>

using namespace std;

/*枚举任务类型*/
enum XTaskType
{
	XTASKTYPE_GAIN,
	XTASKTYPE_NONE
};
/*将配置下的参数设计成任务逐条处理*/
struct XTask
{
	/*任务的类型*/
	XTaskType type;
	/*对应任务的参数*/
	std::vector<double> para;
};

/*抽象类：拥有纯虚函数，无法将其实例化
*另一方面定义为纯虚函数，是为了让继承类只对函数接口做继承，
*继承类需要自己做函数实现
*/
class XVideoFilters
{
public:
	/*需要继承类函数实现得到子类的对象*/
	static XVideoFilters* get();

	/*任务的添加*/
	virtual void add(XTask task) = 0;

	/*任务的清理*/
	virtual void clear() = 0;

	/*根据任务的类型做处理*/
	virtual cv::Mat XPro(cv::Mat mat1, cv::Mat mat2) = 0;

	/*析构函数需要定义为虚函数，因为基类无法实例化，子类实例化后将调用子类的析构函数实现*/
	virtual ~XVideoFilters();

protected:
	XVideoFilters();

};

