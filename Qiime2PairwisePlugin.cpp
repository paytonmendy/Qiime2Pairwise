#include "PluginManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "Qiime2PairwisePlugin.h"

void Qiime2PairwisePlugin::input(std::string file) {
 inputfile = file;
 std::ifstream ifile(inputfile.c_str(), std::ios::in);
 while (!ifile.eof()) {
   std::string key, value;
   ifile >> key;
   ifile >> value;
   parameters[key] = value;
 }
}

void Qiime2PairwisePlugin::run() {

}

void Qiime2PairwisePlugin::output(std::string file) {
   std::string command = "export OLDPATH=${PATH}; ";
   command += "export PATH=${CONDA_HOME}/bin/:${PATH}; ";
   command += "eval \"$(conda shell.bash hook)\"; ";
   command += "conda activate qiime2-2021.4; ";
   command += "qiime longitudinal pairwise-distances  --i-distance-matrix "+std::string(PluginManager::prefix())+"/"+parameters["inputfile"];
   if (parameters.count("metadata") != 0)
	   command += "  --m-metadata-file "+parameters["metadata"];
   if (parameters.count("groupcolumn") != 0)
	   command += " --p-group-column "+parameters["groupcolumn"];
   if (parameters.count("statecolumn") != 0)
	   command += "  --p-state-column "+parameters["statecolumn"];
   if (parameters.count("baselinestate") != 0)
	   command += " --p-state-1 "+parameters["baselinestate"];
   if (parameters.count("pairedstate") != 0)
	   command += "  --p-state-2 "+parameters["pairedstate"];
   if (parameters.count("ID") != 0)
	   command += "  --p-individual-id-column "+parameters["ID"];
   if (parameters.count("parametrictests") != 0)
	   command += "  --p-parametric "+parameters["parametrictests"];
   if (parameters.count("nonparametrictests") != 0)
	   command += " -p-no-parametric "+parameters["nonparametrictests"];
   if (parameters.count("colorpalette") != 0)
	   command += " --p-palette "+parameters["colorpalette"];
   if (parameters.count("repsamples") != 0)
	   command += " --p-replicate-handling "+parameters["repsamples"];

   command += "  --o-visualization; ";
   command += "conda deactivate; ";
   command += "conda deactivate; ";
   command += "export PATH=${OLDPATH}";
 std::cout << command << std::endl;

 system(command.c_str());
}

PluginProxy<Qiime2PairwisePlugin> Qiime2PairwisePluginProxy = PluginProxy<Qiime2PairwisePlugin>("Qiime2Pairwise", PluginManager::getInstance());
