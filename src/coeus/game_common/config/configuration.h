#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include "venus_net/venus_net.h"
#include "config_manager.h"
#include "json/json.h"
#include <fstream>

class Configuration : Json::Reader
{
public:
    // �ó��������������ù�����ע��������
	void initialize(ConfigManager* manager);

    // �÷������ڼ���һ��json�����ļ�����������ڵ������value
    // @filename : json�����ļ���ȫ·��
    // @value    : ����json���ø��ڵ����ݵı���
	bool loadConfig(const std::string& filename, Json::Value& value);

    // ���������ļ����ļ���
    inline const std::string& filename() const { return _filename; }

    // ���������д�÷��������ڶ������ļ����ݽ��н���
	virtual bool parse() = 0;

private:
    std::string _filename;
};

#define LOAD_CONFIG(config_file, value) \
    if (!Configuration::loadConfig(config_file, value)) return false

#endif