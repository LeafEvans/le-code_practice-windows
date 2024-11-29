import os
from collections import Counter


def count_classes(label_dir):
    # 初始化一个Counter来统计类别
    class_counter = Counter()

    # 遍历label_dir下的所有txt文件
    for label_file in os.listdir(label_dir):
        if label_file.endswith('.txt'):
            file_path = os.path.join(label_dir, label_file)
            with open(file_path, 'r') as f:
                # 读取每一行并提取类别ID
                for line in f:
                    class_id = line.split()[0]  # 读取行的第一个元素作为类别ID
                    class_counter[int(class_id)] += 1

    # 获取所有类别ID，并进行重映射（统一映射规则）
    all_classes = sorted(class_counter.keys())
    class_mapping = {
        old_class: new_class
        for new_class, old_class in enumerate(all_classes)
    }

    # 打印重映射后的类别信息
    if all_classes:
        min_class = 0
        max_class = len(all_classes) - 1
        total_classes = len(all_classes)
        print(f"类别从 {min_class} 到 {max_class}, 总共 {total_classes} 个类别")
    else:
        print("未找到任何类别标签")

    # 打印每个类别出现的次数（重映射后）
    for old_class_id, count in class_counter.items():
        new_class_id = class_mapping[old_class_id]
        print(f"类别 {new_class_id}: 出现次数 {count}")

    # 更新所有txt文件中的类别ID，确保映射保持一致
    for label_file in os.listdir(label_dir):
        if label_file.endswith('.txt'):
            file_path = os.path.join(label_dir, label_file)
            updated_lines = []
            with open(file_path, 'r') as f:
                for line in f:
                    parts = line.split()
                    if parts:
                        old_class_id = int(parts[0])
                        new_class_id = class_mapping[old_class_id]
                        parts[0] = str(new_class_id)
                        updated_lines.append(' '.join(parts))
            # 将更新后的内容写回文件
            with open(file_path, 'w') as f:
                for updated_line in updated_lines:
                    f.write(updated_line + '\n')


if __name__ == "__main__":
    label_dir = 'C:\\Scientific Research\\SIETP\\2024\\数据选取\\DAWN\\datasets\\labels\\train'
    count_classes(label_dir)
