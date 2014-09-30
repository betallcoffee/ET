##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=ET
ConfigurationName      :=Debug
WorkspacePath          := "/Users/liang/Workspace/projects/ET/ET"
ProjectPath            := "/Users/liang/Workspace/projects/ET/ET"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=liang
Date                   :=2014-09-25
CodeLitePath           :="/Users/liang/Library/Application Support/codelite"
LinkerName             :=/usr/bin/g++ 
SharedObjectLinkerName :=/usr/bin/g++ -dynamiclib -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/lib$(ProjectName).a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="ET.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++ 
CC       := /usr/bin/gcc 
CXXFLAGS :=  -g $(Preprocessors)
CFLAGS   :=  -g $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as 


##
## User defined environment variables
##
CodeLiteDir:=/Users/liang/Downloads/codelite.app/Contents/SharedSupport/
Objects0=$(IntermediateDirectory)/src_ETAcceptor.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ETBuffer.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ETBufferV.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ETConnection.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ETConnector.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ETEpollSelect.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ETEventLoop.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ETKqueueSelect.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ETSelect.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ETTCPServer.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_ETWatcher.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList) $(ArLibs)
	@$(MakeDirCommand) "/Users/liang/Workspace/projects/ET/ET/.build-debug"
	@echo rebuilt > "/Users/liang/Workspace/projects/ET/ET/.build-debug/ET"

./Debug:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_ETAcceptor.cpp$(ObjectSuffix): ../src/ETAcceptor.cpp $(IntermediateDirectory)/src_ETAcceptor.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/liang/Workspace/projects/ET/src/ETAcceptor.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ETAcceptor.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ETAcceptor.cpp$(DependSuffix): ../src/ETAcceptor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ETAcceptor.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ETAcceptor.cpp$(DependSuffix) -MM "../src/ETAcceptor.cpp"

$(IntermediateDirectory)/src_ETAcceptor.cpp$(PreprocessSuffix): ../src/ETAcceptor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ETAcceptor.cpp$(PreprocessSuffix) "../src/ETAcceptor.cpp"

$(IntermediateDirectory)/src_ETBuffer.cpp$(ObjectSuffix): ../src/ETBuffer.cpp $(IntermediateDirectory)/src_ETBuffer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/liang/Workspace/projects/ET/src/ETBuffer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ETBuffer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ETBuffer.cpp$(DependSuffix): ../src/ETBuffer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ETBuffer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ETBuffer.cpp$(DependSuffix) -MM "../src/ETBuffer.cpp"

$(IntermediateDirectory)/src_ETBuffer.cpp$(PreprocessSuffix): ../src/ETBuffer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ETBuffer.cpp$(PreprocessSuffix) "../src/ETBuffer.cpp"

$(IntermediateDirectory)/src_ETBufferV.cpp$(ObjectSuffix): ../src/ETBufferV.cpp $(IntermediateDirectory)/src_ETBufferV.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/liang/Workspace/projects/ET/src/ETBufferV.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ETBufferV.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ETBufferV.cpp$(DependSuffix): ../src/ETBufferV.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ETBufferV.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ETBufferV.cpp$(DependSuffix) -MM "../src/ETBufferV.cpp"

$(IntermediateDirectory)/src_ETBufferV.cpp$(PreprocessSuffix): ../src/ETBufferV.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ETBufferV.cpp$(PreprocessSuffix) "../src/ETBufferV.cpp"

$(IntermediateDirectory)/src_ETConnection.cpp$(ObjectSuffix): ../src/ETConnection.cpp $(IntermediateDirectory)/src_ETConnection.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/liang/Workspace/projects/ET/src/ETConnection.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ETConnection.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ETConnection.cpp$(DependSuffix): ../src/ETConnection.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ETConnection.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ETConnection.cpp$(DependSuffix) -MM "../src/ETConnection.cpp"

$(IntermediateDirectory)/src_ETConnection.cpp$(PreprocessSuffix): ../src/ETConnection.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ETConnection.cpp$(PreprocessSuffix) "../src/ETConnection.cpp"

$(IntermediateDirectory)/src_ETConnector.cpp$(ObjectSuffix): ../src/ETConnector.cpp $(IntermediateDirectory)/src_ETConnector.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/liang/Workspace/projects/ET/src/ETConnector.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ETConnector.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ETConnector.cpp$(DependSuffix): ../src/ETConnector.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ETConnector.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ETConnector.cpp$(DependSuffix) -MM "../src/ETConnector.cpp"

$(IntermediateDirectory)/src_ETConnector.cpp$(PreprocessSuffix): ../src/ETConnector.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ETConnector.cpp$(PreprocessSuffix) "../src/ETConnector.cpp"

$(IntermediateDirectory)/src_ETEpollSelect.cpp$(ObjectSuffix): ../src/ETEpollSelect.cpp $(IntermediateDirectory)/src_ETEpollSelect.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/liang/Workspace/projects/ET/src/ETEpollSelect.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ETEpollSelect.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ETEpollSelect.cpp$(DependSuffix): ../src/ETEpollSelect.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ETEpollSelect.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ETEpollSelect.cpp$(DependSuffix) -MM "../src/ETEpollSelect.cpp"

$(IntermediateDirectory)/src_ETEpollSelect.cpp$(PreprocessSuffix): ../src/ETEpollSelect.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ETEpollSelect.cpp$(PreprocessSuffix) "../src/ETEpollSelect.cpp"

$(IntermediateDirectory)/src_ETEventLoop.cpp$(ObjectSuffix): ../src/ETEventLoop.cpp $(IntermediateDirectory)/src_ETEventLoop.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/liang/Workspace/projects/ET/src/ETEventLoop.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ETEventLoop.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ETEventLoop.cpp$(DependSuffix): ../src/ETEventLoop.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ETEventLoop.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ETEventLoop.cpp$(DependSuffix) -MM "../src/ETEventLoop.cpp"

$(IntermediateDirectory)/src_ETEventLoop.cpp$(PreprocessSuffix): ../src/ETEventLoop.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ETEventLoop.cpp$(PreprocessSuffix) "../src/ETEventLoop.cpp"

$(IntermediateDirectory)/src_ETKqueueSelect.cpp$(ObjectSuffix): ../src/ETKqueueSelect.cpp $(IntermediateDirectory)/src_ETKqueueSelect.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/liang/Workspace/projects/ET/src/ETKqueueSelect.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ETKqueueSelect.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ETKqueueSelect.cpp$(DependSuffix): ../src/ETKqueueSelect.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ETKqueueSelect.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ETKqueueSelect.cpp$(DependSuffix) -MM "../src/ETKqueueSelect.cpp"

$(IntermediateDirectory)/src_ETKqueueSelect.cpp$(PreprocessSuffix): ../src/ETKqueueSelect.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ETKqueueSelect.cpp$(PreprocessSuffix) "../src/ETKqueueSelect.cpp"

$(IntermediateDirectory)/src_ETSelect.cpp$(ObjectSuffix): ../src/ETSelect.cpp $(IntermediateDirectory)/src_ETSelect.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/liang/Workspace/projects/ET/src/ETSelect.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ETSelect.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ETSelect.cpp$(DependSuffix): ../src/ETSelect.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ETSelect.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ETSelect.cpp$(DependSuffix) -MM "../src/ETSelect.cpp"

$(IntermediateDirectory)/src_ETSelect.cpp$(PreprocessSuffix): ../src/ETSelect.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ETSelect.cpp$(PreprocessSuffix) "../src/ETSelect.cpp"

$(IntermediateDirectory)/src_ETTCPServer.cpp$(ObjectSuffix): ../src/ETTCPServer.cpp $(IntermediateDirectory)/src_ETTCPServer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/liang/Workspace/projects/ET/src/ETTCPServer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ETTCPServer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ETTCPServer.cpp$(DependSuffix): ../src/ETTCPServer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ETTCPServer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ETTCPServer.cpp$(DependSuffix) -MM "../src/ETTCPServer.cpp"

$(IntermediateDirectory)/src_ETTCPServer.cpp$(PreprocessSuffix): ../src/ETTCPServer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ETTCPServer.cpp$(PreprocessSuffix) "../src/ETTCPServer.cpp"

$(IntermediateDirectory)/src_ETWatcher.cpp$(ObjectSuffix): ../src/ETWatcher.cpp $(IntermediateDirectory)/src_ETWatcher.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/liang/Workspace/projects/ET/src/ETWatcher.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ETWatcher.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ETWatcher.cpp$(DependSuffix): ../src/ETWatcher.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ETWatcher.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ETWatcher.cpp$(DependSuffix) -MM "../src/ETWatcher.cpp"

$(IntermediateDirectory)/src_ETWatcher.cpp$(PreprocessSuffix): ../src/ETWatcher.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ETWatcher.cpp$(PreprocessSuffix) "../src/ETWatcher.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) ./Debug/*$(ObjectSuffix)
	$(RM) ./Debug/*$(DependSuffix)
	$(RM) $(OutputFile)
	$(RM) ".build-debug/ET"


