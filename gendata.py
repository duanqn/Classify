import argparse
import random
parser = argparse.ArgumentParser(description='Generate data for Classify project')
parser.add_argument('numStudents', metavar='N_STU', type=int, help='the number of students')
parser.add_argument('numClasses', metavar='N_CLS', type=int, help='the number of classes')
parser.add_argument('numSubjects', metavar='N_SBJ', type=int, help='the number of subjects')
parser.add_argument('--maleRatio', '-m', metavar='male%', default = 0.5, type=float, help='the percentage of male students')
parser.add_argument('--filename', '-f', default='input.txt', type=str, help='the file to save the data')

args = parser.parse_args()

print(args)
random.seed()

with open(args.filename, 'w') as f:
    f.write(str(args.numStudents) + " " + str(args.numClasses) + " " + str(args.numSubjects) + "\n")
    for i in range(0, args.numStudents):
        f.write("Name_" + str(i) + " ")
        randnum = random.random()
        if randnum < args.maleRatio:
            f.write("1 ")
        else:
            f.write("0 ")
        for j in range(0, args.numSubjects):
            f.write(str(random.randrange(20, 101)) + " ")
        f.write("\n")