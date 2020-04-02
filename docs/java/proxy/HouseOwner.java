package cn.junechiu.learnjava.proxy;

/**
 * Created by android on 2017/8/21.
 * 房东类
 */
public class HouseOwner implements RentHouse {

    @Override
    public void rent() {
        System.out.println("i want to rent my house");
    }

    @Override
    public void charge(String str) {
        System.out.println("i will get RMB" + str + " to rent");
    }
}
