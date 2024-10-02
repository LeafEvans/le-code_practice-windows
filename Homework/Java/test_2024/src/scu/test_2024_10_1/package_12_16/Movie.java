package scu.test_2024_10_1.package_12_16;

public class Movie {
    String movieName;
    String director;
    String[] actors = new String[6];

    public void initData() {
        actors[0] = "张路";
        actors[1] = "黄树东";
        actors[2] = "王湖南";
        actors[3] = "李琳";
        actors[4] = "邓爱红";
        actors[5] = "何锐";
    }

    public void show() {
        System.out.println("电影的名称为：" + movieName);
        System.out.println("电影的导演为：" + director);
        System.out.println("电影的参演人员为：");
        for (int i = 0; i < actors.length; ++i) {
            System.out.println(actors[i]);
        }
    }
}
