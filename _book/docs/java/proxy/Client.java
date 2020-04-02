package cn.junechiu.learnjava.proxy;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Proxy;

/**
 * Created by android on 2017/8/21.
 */
public class Client {
    public static void main(String... args) {
        //代理对象
        HouseOwner houseOwner = new HouseOwner();
        //传入代理对象
        InvocationHandler handlerProxy = new DynamicProxy(houseOwner);
    /*
     * 通过Proxy的newProxyInstance方法来创建我们的代理对象，我们来看看其三个参数
     * 第一个参数 handler.getClass().getClassLoader() ，使用handler这个类的ClassLoader对象来加载我们的代理对象
     * 第二个参数realSubject.getClass().getInterfaces()，为代理对象提供的接口是真实对象所实现的接口，
     *         表示我要代理的是该真实对象，这样我就能调用这组接口中的方法了
     * 第三个参数handler， 我们这里将这个代理对象关联到了上方的 InvocationHandler 这个对象上
     */
        RentHouse rentHouse = (RentHouse) Proxy.newProxyInstance(handlerProxy.getClass().getClassLoader(),
                houseOwner.getClass().getInterfaces(), handlerProxy);
        System.out.println(rentHouse.getClass().getName());
        rentHouse.rent();
        rentHouse.charge("10000");
    }
}
