object Facto  {
	def fact(n: Int): BigInt = (2 to n).map(BigInt(_)).par.product // факториал
	def dsum(n: BigInt): Int = n.toString.map(_.asDigit).sum // сумма цифр
	def main(args: Array[String]): Unit = {
		var n = 0;
		if( args.headOption.isDefined ) n = args(0).toInt;
		if( n == 0 ) n = 1000000;
		println( "calculating factorial: " + n + "!" )    	
		println( "result: " + dsum(fact(n)) )
	}
}