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
    # FIXME get the CPPDEFINES and CPPPATH from self instead of hardcode it
    mockme = Action("cd %s && mockme/mockme -Iinclude -Iinclude/mockme/fake_libc $SOURCE -o $TARGET" % Dir("#"),
                    "   MOCK  $SOURCE")
    self.Command(target, source, mockme)
    
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
root.MergeFlags("-Wall -Wextra -O3 -m32")
root.MergeFlags("-ggdb -O0")
Export("root")

SConscript("mockme/SConscript")
SConscript("demo/SConscript")

########################################################################################################################
