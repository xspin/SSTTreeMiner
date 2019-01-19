
def check(f1, f2):
    print("Checking ...")
    print("  ", f1)
    print("  ", f2)
    passed = True
    with open(f1, 'r') as fh1, open(f2,'r') as fh2:
        i = 0
        for line1, line2 in zip(fh1.readlines(), fh2.readlines()):
            i += 1
            if line1 == "Summary\n": break
            if line1 != line2:
                print('    "{}"'.format(line1[:-1]))
                print('    "{}"'.format(line2[:-1]))
                print("  Not Match [line %d]"%i)
                passed = False

    if passed: print("  Pass")

def check_data():
    dirs = ["data/f5", "data/f5leaf", "data/testsst"]
    for d in dirs:
        f1 = d + "/out.data"
        f2 = d + "/outsst.data"
        check(f1, f2)

def check_out():
    dirs = ["data/test/D10", "data/test/F5"]
    for d in dirs:
        f1 = d + "_out.data"
        f2 = d + "_sst_out.data"
        check(f1, f2)

check_out()