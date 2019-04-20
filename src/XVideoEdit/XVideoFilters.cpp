#include "XVideoFilters.h"
#include "XImagePro.h"
#include <QMutex>

class CXFilter : public XVideoFilters
{
public:
	std::vector<XTask> Tasks;

	static CXFilter* get();

	/*任务的添加*/
	void add(XTask task);

	/*任务的清理*/
	void clear();

	/*根据任务的类型做处理*/
	cv::Mat XPro(cv::Mat mat1, cv::Mat mat2);

protected:
	QMutex mutex;
};

/*任务的添加*/
void CXFilter::add(XTask task)
{
	mutex.lock();
	Tasks.push_back(task);
	mutex.unlock();
}

/*任务的清理*/
void CXFilter::clear()
{
	mutex.lock();
	Tasks.clear();
	mutex.unlock();
}

/*根据任务的类型做处理*/
cv::Mat CXFilter::XPro(cv::Mat mat1, cv::Mat mat2)
{
	XImagePro p;
	if (mat1.empty() && mat2.empty())
	{
		return cv::Mat();
	}
	/*图像帧传递给XImagePro处理类*/
	p.set(mat1, mat2);

	mutex.lock();
	for (int i = 0; i < Tasks.size(); i++)
	{
		switch (Tasks[i].type)
		{
		case XTASKTYPE_GAIN:
			p.gain((double)Tasks[i].para[0], (double)Tasks[i].para[1]);
			break;
		default:
			break;
		}	
	}

	cv::Mat re = p.get();
	mutex.unlock();

	return re;
}

/*需要继承类函数实现得到子类的对象*/
/*使用父类做返回值类型，相当于用声明了父类的指针指向了子类对象*/
XVideoFilters* XVideoFilters::get()
{
	static CXFilter cx;
	return &cx;
}

XVideoFilters::XVideoFilters()
{

}


XVideoFilters::~XVideoFilters()
{

}
