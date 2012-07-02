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
    cwd = Dir("#").abspath + "/"
    self.Program(target, source)
    self["TESTBIN"] = os.path.relpath(target, cwd)
    self["TESTRES"] = "${TESTBIN}.res"
    self["TESTCOM"] = "./${TESTBIN} > ${TESTRES}"
    self["TESTCOMSTR"] = "${TESTCOM}" if self["VERBOSE"] else "   TEST  ${TARGET}"
    test = Action("${TESTCOM}", "${TESTCOMSTR}", cwd=cwd)
    self.Command(target + ".res", target, test)
    
def MockMe(self, target, source):
    cwd = Dir("#").abspath + "/"
    self["MOCKMEDEFINES"] = " ".join("-D" + x for x in self.get("CPPDEFINES", []))
    self["MOCKMEPATH"]    = " ".join("-I" + os.path.relpath(str(Dir(x)), cwd) for x in self.get("CPPPATH", []))
    self["FAKE_LIBC"]     = "include/mockme/fake_libc"
    self["MOCKMECOM"]     = "mockme/mockme ${MOCKMEDEFINES} ${MOCKMEPATH} -I${FAKE_LIBC} ${SOURCE} -o ${TARGET}"
    self["MOCKMECOMSTR"]  = "${MOCKMECOM}" if self["VERBOSE"] else "   MOCK  ${TARGET}"
    mockme = Action("${MOCKMECOM}", "${MOCKMECOMSTR}", cwd=cwd)
    self.Command(target, [ source, "#mockme/mockme" ], mockme)
    
AddMethod(Environment, UnitTest)
AddMethod(Environment, MockMe)

########################################################################################################################

variables = Variables()
variables.Add(BoolVariable("VERBOSE", "set to 1 in order to display the build commands as they are executed", True))
    
base = Environment(variables=variables, ENV=os.environ)
base["CC"]           = "gcc -m32"
base["OBJPREFIX"]    = "."

if not base["VERBOSE"]:
    base["CCCOMSTR"]     = "   CC    ${TARGET}"
    base["SHCCCOMSTR"]   = "   CC    ${TARGET}"
    base["SHLINKCOMSTR"] = "   LD    ${TARGET}"
    base["ARCOMSTR"]     = "   AR    ${TARGET}"
    base["LINKCOMSTR"]   = "   LD    ${TARGET}"
    base["RANLIBCOMSTR"] = "   RL    ${TARGET}"
        
Help(variables.GenerateHelpText(base))

########################################################################################################################

root = base.Clone()
root.MergeFlags("-Wall -Wextra -O3")
root.MergeFlags("-ggdb -O0")
Export("root")

SConscript("mockme/SConscript")
SConscript("test/SConscript")
SConscript("demo/SConscript")

########################################################################################################################
