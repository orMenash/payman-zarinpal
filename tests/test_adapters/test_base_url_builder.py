from zarinpal.adapters.base_url_builder import BaseURLBuilder


def test_base_url_production():
    url = BaseURLBuilder(False, 4)
    assert url.startswith("https://www.zarinpal.com")


def test_base_url_sandbox():
    url = BaseURLBuilder(True, 4)
    assert "sandbox.zarinpal.com" in url
