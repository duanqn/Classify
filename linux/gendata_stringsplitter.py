filename = 'stringsplitter.test.txt'
with open(filename, 'w') as fout:
    while True:
        line = input()
        if not line:
            break
        delimiter = input('Please give delimiter: ')
        delimiter = delimiter[0]
        segs = line.split(delimiter)
        fout.write(line + '\n')
        fout.write(str(len(segs)) + ' ' + delimiter + '\n')
        for seg in segs:
            fout.write(seg + '\n')