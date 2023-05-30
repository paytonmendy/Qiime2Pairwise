#ifndef QIIME2PAIRWISEPLUGIN_H
#define QIIME2PAIRWISEPLUGIN_H

#include "Plugin.h"
#include "PluginProxy.h"
#include <string>
#include <vector>

class Qiime2PairwisePlugin : public Plugin
{
public: 
 std::string toString() {return "Qiime2Pairwise";}
 void input(std::string file);
 void run();
 void output(std::string file);

private: 
 std::string inputfile;
 std::string outputfile;
 std::map<std::string, std::string> parameters;

};

#endif
