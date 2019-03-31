#pragma once
#include <opencv2/core.hpp>
#include <vector>

using namespace std;

/*ö����������*/
enum XTaskType
{
	XTASKTYPE_GAIN,
	XTASKTYPE_NONE
};
/*�������µĲ�����Ƴ�������������*/
struct XTask
{
	/*���������*/
	XTaskType type;
	/*��Ӧ����Ĳ���*/
	std::vector<double> para;
};

/*�����ࣺӵ�д��麯�����޷�����ʵ����
*��һ���涨��Ϊ���麯������Ϊ���ü̳���ֻ�Ժ����ӿ����̳У�
*�̳�����Ҫ�Լ�������ʵ��
*/
class XVideoFilters
{
public:
	/*��Ҫ�̳��ຯ��ʵ�ֵõ�����Ķ���*/
	static XVideoFilters* get();

	/*��������*/
	virtual void add(XTask task) = 0;

	/*���������*/
	virtual void clear() = 0;

	/*�������������������*/
	virtual cv::Mat XPro(cv::Mat mat1, cv::Mat mat2) = 0;

	/*����������Ҫ����Ϊ�麯������Ϊ�����޷�ʵ����������ʵ�����󽫵����������������ʵ��*/
	virtual ~XVideoFilters();

protected:
	XVideoFilters();

};

