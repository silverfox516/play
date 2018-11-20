import igsong.MyClass;

import java.util.ArrayList;

public class Test
{
	public static void main(String[] args) {
		ArrayList<MyClass> alsrc = new ArrayList<MyClass>();
		ArrayList<MyClass> alcopy = new ArrayList<MyClass>();

		for (int i = 0; i < 10; ++i)
			alsrc.add(new MyClass(i));

		for (MyClass item : alsrc)
			alcopy.add(item);

		System.out.println("print alsrc and change");
		for (MyClass item : alsrc) {
			System.out.println(item.getId());
			item.setId(item.getId() * item.getId());
		}

		System.out.println("print alcopy");
		for (MyClass item : alcopy)
			System.out.println(item.getId());
	}
}
