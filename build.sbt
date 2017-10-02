import sbt.Keys.{ivyXML, scalaVersion}

name := "noise-analyzer"

shellPrompt in ThisBuild := { state => s"${Project.extract(state).currentRef.project}-${version.value}> " }

lazy val commonSettings = Seq(
  scalaVersion := "2.11.8",

  scalacOptions ++= Seq("-deprecation", "-unchecked", "-feature", "-Xlint", "-language:postfixOps",
    "-language:implicitConversions", "-language:higherKinds"),

  fork := true,

  resolvers ++= Seq(
  )
)

lazy val analyzer = Project(
  id = "noise-analyzer",
  base = file("noise-analyzer")
).settings(commonSettings)

