def analyze_grades(grades):
    avg = sum(grades) / len(grades)
    if avg >= 60:
        result = "Pass"
    else:
        result = "Fail"
    return avg, result

grades = [30, 40, 52, 51, 35]
average, status = analyze_grades(grades)
print(average, status)