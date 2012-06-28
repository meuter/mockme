import os

########################################################################################################################

Alias("all", ".")
CacheDir("/tmp/")
Decider('MD5-timestamp')
SetOption('max_drift', 1)
SetOption('implicit_cache', 1)
SourceCode(".", None)
SetOption('num_jobs', 3)

########################################################################################################################

def UnitTest(self, target, source):
    program = self.Program(target, source)
    display_target = os.path.abspath(target).replace(Dir("#").abspath + "/", "")
    target = os.path.abspath(target)
    source = [ os.path.abspath(file) for file in source ]
    action = self.Action(target + " > " + target.strip() + ".res", "   TEST  " + display_target)
    self.Command(target + ".res", target, action)
    
def MockMe(self, target, source):
    self["MOCKME_DEFINES"] = " ".join("-D" + x for x in self["CPPDEFINES"])
    self["MOCKME_PATH"]    = " ".join("-I" + str(Dir(x)) for x in self["CPPPATH"])
    self["SCONS_ROOT"]     = Dir("#").abspath + "/"
    mockme = Action("${SCONS_ROOT}mockme/mockme $MOCKME_DEFINES $MOCKME_PATH -I${SCONS_ROOT}include/mockme/fake_libc $SOURCE -o $TARGET",
                    "   MOCK  ${TARGET}")
    self.Command(target, [ source, "#mockme/mockme" ], mockme)
    
########################################################################################################################

base = Environment()
AddMethod(Environment, UnitTest)
AddMethod(Environment, MockMe)
base["CC"]           = "gcc -m32"
base["CCCOMSTR"]     = "   CC    ${TARGET}"
base["SHCCCOMSTR"]   = "   CC    ${TARGET}"
base["SHLINKCOMSTR"] = "   LD    ${TARGET}"
base["ARCOMSTR"]     = "   AR    ${TARGET}"
base["LINKCOMSTR"]   = "   LD    ${TARGET}"
base["RANLIBCOMSTR"] = "   RL    ${TARGET}"
base["OBJPREFIX"]    = "."

########################################################################################################################

root = base.Clone()
root.MergeFlags("-Wall -Wextra -O3")
root.MergeFlags("-ggdb -O0")
Export("root")

SConscript("mockme/SConscript")
SConscript("demo/SConscript")

########################################################################################################################
