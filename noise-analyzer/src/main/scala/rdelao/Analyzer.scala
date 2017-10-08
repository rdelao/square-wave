package rdelao

import breeze.linalg.DenseVector
import breeze.plot.Figure
import com.typesafe.config.ConfigFactory
import breeze.plot._
import DomainFunction._

import scala.io.Source

/**
  * Created by ryan on 10/1/17.
  */
object Analyzer {

  type DataPoint = (Double, Double)

  def plotData(dataFileLines: Iterator[String]): Unit = {
    val fig = Figure()
    fig.height_=(780)
    fig.width_=(2160)
    val plt = fig.subplot(0)
    plt.xlabel_=("nanosecond")
    plt.ylabel_=("amplitude")
    val (time, amp) = dataFileLines.foldLeft(Vector.empty[Double], Vector.empty[Double]) {
      (acc: (Vector[Double], Vector[Double]), line: String) =>
        val data = line.split(',')
        val dataPoint: DataPoint = (data.apply(0).toDouble, data.apply(1).toDouble)
        (acc._1 :+ dataPoint._1, acc._2 :+ dataPoint._2)
      }
    val uniques = amp.toSet
    val hidden_amplitude = uniques.find { u =>
      amp.count(_ == u) == 10D
    }.getOrElse(0D)
    val hiddenAmp = amp.map { a =>
      if (a == hidden_amplitude) hidden_amplitude else 0D
    }
    val test = time.map(_ => 1D)
    val timePlt: DenseVector[Double] = DenseVector(time: _*)
    val ampPlt: DenseVector[Double] = DenseVector(amp: _*)
    plt += plot(timePlt, ampPlt, name = "White Noise")
    fig.refresh()
    plt += plot(timePlt, hiddenAmp, name = "Hidden signal", colorcode = "red")
    fig.refresh()
    fig.saveas("noise.png")
  }

  /** Main entry point to the program */
  def main(args: Array[String]): Unit = {
    val config = ConfigFactory.defaultApplication().resolve()
    val settings = Settings(config)
    plotData(Source.fromFile(settings.dataFileName).getLines())
  }
}
