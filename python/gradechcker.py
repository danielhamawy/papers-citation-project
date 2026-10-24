students = {"Alex":[91,82,79],"Danny":[97,81,94],"Jake":[81,20,31],"carole":[30,21,45]}
def average(grades):
    avg = sum(grades)//len(grades)
    return avg
def get_status(avg):
    if avg>60:
        return"pass"
    else:
        return"fail"
for name,grades in students.items():
    AM = average(grades)
    Status = get_status(AM)
    print(f"{name} has an average grade of {AM} and he got a {Status}")
stud = [name for name,grades in students.items() if average(grades)>60]
print(stud)
search = input("Enter the name you are searching for: ")
if search in students:
    grades = students[search]
    print(f"{search} got average of: {average(grades)}")
else:
    print("not found")