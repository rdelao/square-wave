package rdelao

import com.typesafe.config.Config

case class Settings(dataFileName: String)

object Settings {
  def apply(config: Config): Settings = {
    Settings(config.getString("data_file"))
  }
}