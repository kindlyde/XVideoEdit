#include "XVideoFilters.h"
#include "XImagePro.h"
#include <QMutex>

class CXFilter : public XVideoFilters
{
public:
	std::vector<XTask> Tasks;

	static CXFilter* get();

	/*��������*/
	void add(XTask task);

	/*���������*/
	void clear();

	/*�������������������*/
	cv::Mat XPro(cv::Mat mat1, cv::Mat mat2);

protected:
	QMutex mutex;
};

/*��������*/
void CXFilter::add(XTask task)
{
	mutex.lock();
	Tasks.push_back(task);
	mutex.unlock();
}

/*���������*/
void CXFilter::clear()
{
	mutex.lock();
	Tasks.clear();
	mutex.unlock();
}

/*�������������������*/
cv::Mat CXFilter::XPro(cv::Mat mat1, cv::Mat mat2)
{
	XImagePro p;
	if (mat1.empty() && mat2.empty())
	{
		return cv::Mat();
	}
	/*ͼ��֡���ݸ�XImagePro������*/
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

/*��Ҫ�̳��ຯ��ʵ�ֵõ�����Ķ���*/
/*ʹ�ø���������ֵ���ͣ��൱���������˸����ָ��ָ�����������*/
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
