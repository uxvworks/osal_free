##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=osal_free
ConfigurationName      :=Debug
WorkspacePath          := "/media/TI106400W0E/code/uxvworks_code/uxvworks"
ProjectPath            := "/media/TI106400W0E/code/uxvworks_code/osal_free/test"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=yeager
Date                   :=10/05/2013
CodeLitePath           :="/home/yeager/.codelite"
LinkerName             :=gcc
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)RMX_OSAL_PTHREAD 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="osal_free.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)../../ $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)pthread $(LibrarySwitch)rt 
ArLibs                 :=  "pthread" "rt" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := gcc
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/osal_free_osal$(ObjectSuffix) $(IntermediateDirectory)/osal_free_osal_memory$(ObjectSuffix) $(IntermediateDirectory)/osal_free_osal_msg_q$(ObjectSuffix) $(IntermediateDirectory)/osal_free_osal_mutex$(ObjectSuffix) $(IntermediateDirectory)/osal_free_osal_thread$(ObjectSuffix) $(IntermediateDirectory)/osal_free_osal_timer$(ObjectSuffix) $(IntermediateDirectory)/spsc_fifo_byte_spsc_fifo$(ObjectSuffix) $(IntermediateDirectory)/spsc_fifo_ptr_spsc_fifo$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.c $(IntermediateDirectory)/main$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/TI106400W0E/code/uxvworks_code/osal_free/test/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "main.c"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "main.c"

$(IntermediateDirectory)/osal_free_osal$(ObjectSuffix): ../osal.c $(IntermediateDirectory)/osal_free_osal$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/TI106400W0E/code/uxvworks_code/osal_free/osal.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/osal_free_osal$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/osal_free_osal$(DependSuffix): ../osal.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/osal_free_osal$(ObjectSuffix) -MF$(IntermediateDirectory)/osal_free_osal$(DependSuffix) -MM "../osal.c"

$(IntermediateDirectory)/osal_free_osal$(PreprocessSuffix): ../osal.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/osal_free_osal$(PreprocessSuffix) "../osal.c"

$(IntermediateDirectory)/osal_free_osal_memory$(ObjectSuffix): ../osal_memory.c $(IntermediateDirectory)/osal_free_osal_memory$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/TI106400W0E/code/uxvworks_code/osal_free/osal_memory.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/osal_free_osal_memory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/osal_free_osal_memory$(DependSuffix): ../osal_memory.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/osal_free_osal_memory$(ObjectSuffix) -MF$(IntermediateDirectory)/osal_free_osal_memory$(DependSuffix) -MM "../osal_memory.c"

$(IntermediateDirectory)/osal_free_osal_memory$(PreprocessSuffix): ../osal_memory.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/osal_free_osal_memory$(PreprocessSuffix) "../osal_memory.c"

$(IntermediateDirectory)/osal_free_osal_msg_q$(ObjectSuffix): ../osal_msg_q.c $(IntermediateDirectory)/osal_free_osal_msg_q$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/TI106400W0E/code/uxvworks_code/osal_free/osal_msg_q.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/osal_free_osal_msg_q$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/osal_free_osal_msg_q$(DependSuffix): ../osal_msg_q.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/osal_free_osal_msg_q$(ObjectSuffix) -MF$(IntermediateDirectory)/osal_free_osal_msg_q$(DependSuffix) -MM "../osal_msg_q.c"

$(IntermediateDirectory)/osal_free_osal_msg_q$(PreprocessSuffix): ../osal_msg_q.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/osal_free_osal_msg_q$(PreprocessSuffix) "../osal_msg_q.c"

$(IntermediateDirectory)/osal_free_osal_mutex$(ObjectSuffix): ../osal_mutex.c $(IntermediateDirectory)/osal_free_osal_mutex$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/TI106400W0E/code/uxvworks_code/osal_free/osal_mutex.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/osal_free_osal_mutex$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/osal_free_osal_mutex$(DependSuffix): ../osal_mutex.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/osal_free_osal_mutex$(ObjectSuffix) -MF$(IntermediateDirectory)/osal_free_osal_mutex$(DependSuffix) -MM "../osal_mutex.c"

$(IntermediateDirectory)/osal_free_osal_mutex$(PreprocessSuffix): ../osal_mutex.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/osal_free_osal_mutex$(PreprocessSuffix) "../osal_mutex.c"

$(IntermediateDirectory)/osal_free_osal_thread$(ObjectSuffix): ../osal_thread.c $(IntermediateDirectory)/osal_free_osal_thread$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/TI106400W0E/code/uxvworks_code/osal_free/osal_thread.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/osal_free_osal_thread$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/osal_free_osal_thread$(DependSuffix): ../osal_thread.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/osal_free_osal_thread$(ObjectSuffix) -MF$(IntermediateDirectory)/osal_free_osal_thread$(DependSuffix) -MM "../osal_thread.c"

$(IntermediateDirectory)/osal_free_osal_thread$(PreprocessSuffix): ../osal_thread.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/osal_free_osal_thread$(PreprocessSuffix) "../osal_thread.c"

$(IntermediateDirectory)/osal_free_osal_timer$(ObjectSuffix): ../osal_timer.c $(IntermediateDirectory)/osal_free_osal_timer$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/TI106400W0E/code/uxvworks_code/osal_free/osal_timer.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/osal_free_osal_timer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/osal_free_osal_timer$(DependSuffix): ../osal_timer.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/osal_free_osal_timer$(ObjectSuffix) -MF$(IntermediateDirectory)/osal_free_osal_timer$(DependSuffix) -MM "../osal_timer.c"

$(IntermediateDirectory)/osal_free_osal_timer$(PreprocessSuffix): ../osal_timer.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/osal_free_osal_timer$(PreprocessSuffix) "../osal_timer.c"

$(IntermediateDirectory)/spsc_fifo_byte_spsc_fifo$(ObjectSuffix): ../../spsc_fifo/byte_spsc_fifo.c $(IntermediateDirectory)/spsc_fifo_byte_spsc_fifo$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/TI106400W0E/code/uxvworks_code/spsc_fifo/byte_spsc_fifo.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/spsc_fifo_byte_spsc_fifo$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/spsc_fifo_byte_spsc_fifo$(DependSuffix): ../../spsc_fifo/byte_spsc_fifo.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/spsc_fifo_byte_spsc_fifo$(ObjectSuffix) -MF$(IntermediateDirectory)/spsc_fifo_byte_spsc_fifo$(DependSuffix) -MM "../../spsc_fifo/byte_spsc_fifo.c"

$(IntermediateDirectory)/spsc_fifo_byte_spsc_fifo$(PreprocessSuffix): ../../spsc_fifo/byte_spsc_fifo.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/spsc_fifo_byte_spsc_fifo$(PreprocessSuffix) "../../spsc_fifo/byte_spsc_fifo.c"

$(IntermediateDirectory)/spsc_fifo_ptr_spsc_fifo$(ObjectSuffix): ../../spsc_fifo/ptr_spsc_fifo.c $(IntermediateDirectory)/spsc_fifo_ptr_spsc_fifo$(DependSuffix)
	$(CC) $(SourceSwitch) "/media/TI106400W0E/code/uxvworks_code/spsc_fifo/ptr_spsc_fifo.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/spsc_fifo_ptr_spsc_fifo$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/spsc_fifo_ptr_spsc_fifo$(DependSuffix): ../../spsc_fifo/ptr_spsc_fifo.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/spsc_fifo_ptr_spsc_fifo$(ObjectSuffix) -MF$(IntermediateDirectory)/spsc_fifo_ptr_spsc_fifo$(DependSuffix) -MM "../../spsc_fifo/ptr_spsc_fifo.c"

$(IntermediateDirectory)/spsc_fifo_ptr_spsc_fifo$(PreprocessSuffix): ../../spsc_fifo/ptr_spsc_fifo.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/spsc_fifo_ptr_spsc_fifo$(PreprocessSuffix) "../../spsc_fifo/ptr_spsc_fifo.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/osal_free_osal$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/osal_free_osal$(DependSuffix)
	$(RM) $(IntermediateDirectory)/osal_free_osal$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/osal_free_osal_memory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/osal_free_osal_memory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/osal_free_osal_memory$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/osal_free_osal_msg_q$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/osal_free_osal_msg_q$(DependSuffix)
	$(RM) $(IntermediateDirectory)/osal_free_osal_msg_q$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/osal_free_osal_mutex$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/osal_free_osal_mutex$(DependSuffix)
	$(RM) $(IntermediateDirectory)/osal_free_osal_mutex$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/osal_free_osal_thread$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/osal_free_osal_thread$(DependSuffix)
	$(RM) $(IntermediateDirectory)/osal_free_osal_thread$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/osal_free_osal_timer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/osal_free_osal_timer$(DependSuffix)
	$(RM) $(IntermediateDirectory)/osal_free_osal_timer$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/spsc_fifo_byte_spsc_fifo$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/spsc_fifo_byte_spsc_fifo$(DependSuffix)
	$(RM) $(IntermediateDirectory)/spsc_fifo_byte_spsc_fifo$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/spsc_fifo_ptr_spsc_fifo$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/spsc_fifo_ptr_spsc_fifo$(DependSuffix)
	$(RM) $(IntermediateDirectory)/spsc_fifo_ptr_spsc_fifo$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "../../uxvworks/.build-debug/osal_free"


